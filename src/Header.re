module Styles = {
  open Css;
  let header =
    style([
      position(fixed),
      display(`flex),
      top(px(0)),
      left(px(0)),
      flexDirection(column),
      alignItems(flexStart),
      fontFamily("mr-eaves-xl-modern, sans-serif"),
      paddingLeft(vw(10.0)),
    ]);
};

let component = ReasonReact.statelessComponent("App");
open Types;
let make = (~currentSession, ~deleteSession, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  render: _self => {
    <div className=Styles.header>
      <Link href="/"> <h1> {ReasonReact.string("Elysium")} </h1> </Link>
      {switch (currentSession) {
       | Some(session) =>
         <div>
           <h2> <a href="#" onClick={_ => deleteSession()}> {ReasonReact.string("Sign out")} </a> </h2>
           <Link href="/submit"> <h2> {ReasonReact.string("Submit a project")} </h2> </Link>
           <h2> {ReasonReact.string("Welcome " ++ session.user.displayName)} </h2>
         </div>
       | None => <div> <Link href="/login"> <h2> {ReasonReact.string("Login")} </h2> </Link> </div>
       }}
    </div>;
  },
};
