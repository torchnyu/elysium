type state = {isSubmitting: bool};

type actions =
  | SubmitForm
  | FinishSubmit;

let component = ReasonReact.reducerComponent("ProjectForm");

module SubmitProjectParams = {
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
       $color: String!,
       $token: String!
     ) {
       createProject(
         name: $name,
         description: $description,
         repositoryUrl: $repositoryUrl,
         color: $color,
         token: $token
       ) {
         token
         project {
           id
           slug
         }
       }
  }
  |}
];

module CreateProjectMutation = ReasonApollo.CreateMutation(CreateProject);

module SubmitProjectForm = ReForm.Create(SubmitProjectParams);

open Types;
open ReasonApolloTypes;
exception GraphQLErrors(array(graphqlError));
exception EmptyResponse;

let make = (~session, ~createSession, _children) => {
  ...component,
  initialState: () => {isSubmitting: false},
  reducer: (action, _state) =>
    switch (action) {
    | SubmitForm => ReasonReact.Update({isSubmitting: true})
    | FinishSubmit => ReasonReact.Update({isSubmitting: false})
    },
  render: self => {
    <div>
      <h1> {ReasonReact.string("New Project")} </h1>
      <CreateProjectMutation>
        ...{(mutation, _) =>
          <SubmitProjectForm
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
                    ~color="DD1155",
                    (),
                  );
                mutation(~variables=projectQuery##variables, ())
                |> Js.Promise.then_(res => {
                     self.ReasonReact.send(FinishSubmit);
                     switch (res) {
                     | Data(data) =>
                       let session = {...session, token: data##createProject##token};
                       let projectSlug = data##createProject##project##slug;
                       createSession(session);
                       ReasonReact.Router.push("/projects/" ++ projectSlug);
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
                <label>
                  {ReasonReact.string("Name: ")}
                  <input
                    value={form.values.name}
                    onChange={ReForm.Helpers.handleDomFormChange(handleChange(`name))}
                  />
                </label>
                <p> {getErrorForField(`name) |> Belt.Option.getWithDefault(_, "") |> ReasonReact.string} </p>
                <label>
                  {ReasonReact.string("Description: ")}
                  <input
                    value={form.values.description}
                    onChange={ReForm.Helpers.handleDomFormChange(handleChange(`description))}
                  />
                </label>
                <p> {getErrorForField(`description) |> Belt.Option.getWithDefault(_, "") |> ReasonReact.string} </p>
                <label>
                  {ReasonReact.string("Repository URL: ")}
                  <input
                    value={form.values.repositoryUrl}
                    onChange={ReForm.Helpers.handleDomFormChange(handleChange(`repositoryUrl))}
                  />
                </label>
                <p>
                  {getErrorForField(`repositoryUrl) |> Belt.Option.getWithDefault(_, "") |> ReasonReact.string}
                </p>
                <button disabled={self.state.isSubmitting} type_="submit"> {"Submit" |> ReasonReact.string} </button>
              </form>
            }
          </SubmitProjectForm>
        }
      </CreateProjectMutation>
    </div>;
  },
};
