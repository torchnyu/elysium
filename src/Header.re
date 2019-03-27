module Styles = {
  open Css;
  let header =
    style([
      position(fixed),
      display(`flex),
      top(px(0)),
      left(px(0)),
      flexDirection(row),
      alignItems(flexStart),
      fontFamily("mr-eaves-xl-modern, sans-serif"),
      paddingLeft(vw(10.0)),
    ]);

  let links = style([display(`flex), justifyContent(flexEnd), width(vw(80.0))]);
  let link = style([padding(px(20))]);
};

let component = ReasonReact.statelessComponent("App");
let make = (~currentSession, ~deleteSession, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  render: _self => {
    <div className=Styles.header>
      <Link href="/"> <h1> {ReasonReact.string("Elysium")} </h1> </Link>
      <div className=Styles.links>
        ...{
             switch (currentSession) {
             | Some(_session) => [|
                 <a href="#" onClick={_ => deleteSession()}> <h2> {ReasonReact.string("Sign out")} </h2> </a>,
                 <Link href="/submit"> <h2> {ReasonReact.string("Submit a project")} </h2> </Link>,
               |]
             | None => [|
                 <Link className=Styles.link href="/organizers">
                   <h2> {ReasonReact.string("Organizers")} </h2>
                 </Link>,
                 <Link className=Styles.link href="/login"> <h2> {ReasonReact.string("Login")} </h2> </Link>,
                 <Link className=Styles.link href="/signup"> <h2> {ReasonReact.string("Sign Up")} </h2> </Link>,
               |]
             }
           }
      </div>
    </div>;
  },
};
