type state = {isSubmitting: bool};

type actions =
  | SubmitForm
  | FinishSubmit;

open Types;

module Login = [%graphql
  {| mutation login($email: String!, $password: String!) {
       login(email: $email, password: $password) {
         token
         user {
           id
           displayName
         }
       }
  }
  |}
];

module LoginMutation = ReasonApollo.CreateMutation(Login);

module LoginParams = {
  type state = {
    email: string,
    password: string,
  };
  type fields = [ | `email | `password];
  let lens = [
    (`email, s => s.email, (s, email) => {...s, email}),
    (`password, s => s.password, (s, password) => {...s, password}),
  ];
};

open ReasonApolloTypes;
module LoginForm = ReForm.Create(LoginParams);
exception GraphQLErrors(array(graphqlError));
exception EmptyResponse;

[@react.component]
let make = (~createSession) => {
  let (isSubmitting, setIsSubmitting) = React.useState(() => false);

  <div>
    <h1> {React.string("Login")} </h1>
    <LoginMutation>
      ...{(mutation, _) =>
        <LoginForm
          onSubmit={({values}) => {
            setIsSubmitting(_ => true);
            let loginQuery = Login.make(~email=values.email, ~password=values.password, ());
            mutation(~variables=loginQuery##variables, ())
            |> Js.Promise.then_(res => {
                 setIsSubmitting(_ => false);
                 switch (res) {
                 | Data(data) =>
                   let user = userFromJs(data##login##user);
                   let session = {token: data##login##token, user};
                   createSession(session);
                   Js.Promise.resolve();
                 | Errors(errs) =>
                   Js.log(errs);
                   Js.Promise.reject(raise(GraphQLErrors(errs)));
                 | EmptyResponse => Js.Promise.reject(raise(EmptyResponse))
                 };
               })
            |> ignore;
            ();
          }}
          initialState={email: "", password: ""}
          schema=[(`email, Email), (`password, Required)]>
          ...{({handleSubmit, handleChange, form, getErrorForField}) =>
            <form onSubmit={ReForm.Helpers.handleDomFormSubmit(handleSubmit)}>
              <Input
                label="Email: "
                value={form.values.email}
                error={getErrorForField(`email)}
                onChange={ReForm.Helpers.handleDomFormChange(handleChange(`email))}
              />
              <Input
                label="Password: "
                value={form.values.password}
                error={getErrorForField(`password)}
                type_="password"
                onChange={ReForm.Helpers.handleDomFormChange(handleChange(`password))}
              />
              <Button disabled=isSubmitting type_="submit"> {"SUBMIT" |> React.string} </Button>
            </form>
          }
        </LoginForm>
      }
    </LoginMutation>
  </div>;
};
