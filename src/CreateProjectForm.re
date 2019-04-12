type actions =
  | FinishSubmit
  | SubmitForm;

type state = {isSubmitting: bool};

let component = ReasonReact.reducerComponent("CreateProjectForm");

module CreateProjectParams = {
  type state = {
    name: string,
    description: string,
    repositoryUrl: string,
  };
  type fields = [ | `name | `description | `repositoryUrl];
  let lens = [
    (`name, s => s.name, (s, name) => {...s, name}),
    (`description, s => s.description, (s, description) => {...s, description}),
    (`repositoryUrl, s => s.repositoryUrl, (s, repositoryUrl) => {...s, repositoryUrl}),
  ];
};

module CreateProject = [%graphql
  {| mutation createProject(
       $name: String!,
       $description: String!,
       $repositoryUrl: String!,
       $token: String!
       $eventSlug: String!
     ) {
       createProject(
         project: {
           name: $name,
           description: $description,
           repositoryUrl: $repositoryUrl,
           eventSlug: $eventSlug
         },
         token: $token
       ) {
         token
         project {
           id
           slug
           title
           description
         }
       }
  }
  |}
];

module CreateProjectMutation = ReasonApollo.CreateMutation(CreateProject);
module CreateProjectForm = ReForm.Create(CreateProjectParams);

open Types;
open ReasonApolloTypes;
exception GraphQLErrors(array(graphqlError));
exception EmptyResponse;

let make = (~eventSlug, ~session, ~finishSubmitProject, _children) => {
  ...component,
  initialState: () => {isSubmitting: false},
  reducer: (action, _state) =>
    switch (action) {
    | SubmitForm => ReasonReact.Update({isSubmitting: true})
    | FinishSubmit => ReasonReact.Update({isSubmitting: false})
    },
  render: self =>
    <CreateProjectMutation>
      ...{(mutation, _) =>
        <CreateProjectForm
          onSubmit={({values}) =>
            switch (session) {
            | None => ReasonReact.Router.push("/login")
            | Some((session: session)) =>
              let projectQuery =
                CreateProject.make(
                  ~name=values.name,
                  ~description=values.description,
                  ~repositoryUrl=values.repositoryUrl,
                  ~token=session.token,
                  ~eventSlug,
                  (),
                );
              mutation(~variables=projectQuery##variables, ())
              |> Js.Promise.then_(res => {
                   self.ReasonReact.send(FinishSubmit);
                   switch (res) {
                   | Data(data) =>
                     let session = {...session, token: data##createProject##token};
                     finishSubmitProject(session, projectFromJs(data##createProject##project));
                     Js.Promise.resolve();
                   | Errors(errs) =>
                     Js.log(errs);
                     Js.Promise.reject(raise(GraphQLErrors(errs)));
                   | EmptyResponse => Js.Promise.reject(raise(EmptyResponse))
                   };
                 })
              |> ignore;
              ();
            }
          }
          initialState={name: "", description: "", repositoryUrl: ""}
          schema=[(`name, Required)]>
          ...{({handleSubmit, handleChange, form, getErrorForField}) =>
            <form onSubmit={ReForm.Helpers.handleDomFormSubmit(handleSubmit)}>
              <Input
                label="Name:"
                error={getErrorForField(`name)}
                value={form.values.name}
                onChange={ReForm.Helpers.handleDomFormChange(handleChange(`name))}
              />
              <Input
                label="Description:"
                error={getErrorForField(`description)}
                value={form.values.description}
                onChange={ReForm.Helpers.handleDomFormChange(handleChange(`description))}
              />
              <Input
                label="Repository URL:"
                error={getErrorForField(`repositoryUrl)}
                value={form.values.repositoryUrl}
                onChange={ReForm.Helpers.handleDomFormChange(handleChange(`repositoryUrl))}
              />
              <Button disabled={self.state.isSubmitting} type_="submit"> {"Submit" |> ReasonReact.string} </Button>
            </form>
          }
        </CreateProjectForm>
      }
    </CreateProjectMutation>,
};
