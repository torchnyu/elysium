let component = ReasonReact.statelessComponent("ProjectForm");

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

module LoginForm = ReForm.Create(LoginParams);
open Types;
let make = (~createSession, _children) => {
  ...component,
  render: _self => {
    <div>
      <h1> {ReasonReact.string("New Project")} </h1>
      <LoginMutation>
        ...{(mutation, _) =>
          <LoginForm
            onSubmit={({values}) => {
              let loginQuery = Login.make(~email=values.email, ~password=values.password, ());
              mutation(~variables=loginQuery##variables, ())
              |> Js.Promise.then_(res => {
                   let session = sessionFromJs(res##login);
                   createSession(session);
                 })
              |> Js.Promise.catch(err => {
                   Js.log(err);
                   Js.Promise.resolve(err);
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
                <button type_="submit"> {"Submit" |> ReasonReact.string} </button>
              </form>
            }
          </LoginForm>
        }
      </LoginMutation>
    </div>;
  },
};
