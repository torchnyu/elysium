type state = {isSubmitting: bool};

type actions =
  | SubmitForm
  | FinishSubmit;

let component = ReasonReact.reducerComponent("ProjectForm");

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

let make = (~createSession, _children) => {
  ...component,
  initialState: () => {isSubmitting: false},
  reducer: (action, _state) =>
    switch (action) {
    | SubmitForm => ReasonReact.Update({isSubmitting: true})
    | FinishSubmit => ReasonReact.Update({isSubmitting: false})
    },
  render: self => {
    <div>
      <h1> {ReasonReact.string("Login")} </h1>
      <LoginMutation>
        ...{(mutation, _) =>
          <LoginForm
            onSubmit={({values}) => {
              let loginQuery = Login.make(~email=values.email, ~password=values.password, ());
              mutation(~variables=loginQuery##variables, ())
              |> Js.Promise.then_(res => {
                   self.ReasonReact.send(FinishSubmit);
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
                <label>
                  {ReasonReact.string("Email: ")}
                  <input
                    value={form.values.email}
                    onChange={ReForm.Helpers.handleDomFormChange(handleChange(`email))}
                  />
                </label>
                <p> {getErrorForField(`email) |> Belt.Option.getWithDefault(_, "") |> ReasonReact.string} </p>
                <label>
                  {ReasonReact.string("Password: ")}
                  <input
                    value={form.values.password}
                    type_="password"
                    onChange={ReForm.Helpers.handleDomFormChange(handleChange(`password))}
                  />
                </label>
                <p> {getErrorForField(`password) |> Belt.Option.getWithDefault(_, "") |> ReasonReact.string} </p>
                <button disabled={self.state.isSubmitting} type_="submit"> {"Submit" |> ReasonReact.string} </button>
              </form>
            }
          </LoginForm>
        }
      </LoginMutation>
    </div>;
  },
};
