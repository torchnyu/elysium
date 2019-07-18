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

[@react.component]
let make = (~eventSlug, ~session, ~finishSubmitProject) => {
  let (isSubmitting, setIsSubmitting) = React.useState(() => false);
  <CreateProjectMutation>
    ...{(mutation, _) =>
      <CreateProjectForm
        onSubmit={({values}) =>
          switch (session) {
          | None => ReasonReact.Router.push("/login")
          | Some((session: session)) =>
            setIsSubmitting(_ => true);
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
                 setIsSubmitting(_ => false);
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
            <Button disabled=isSubmitting type_="submit"> {"Submit" |> React.string} </Button>
          </form>
        }
      </CreateProjectForm>
    }
  </CreateProjectMutation>;
};
