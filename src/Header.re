module Styles = {
  open Css;
  let header =
    style([
      display(`flex),
      flexDirection(row),
      alignItems(flexStart),
      justifyContent(center),
      backgroundColor(Theme.darkBlue),
      width(vw(100.)),
      padding4(~top=px(10), ~left=px(0), ~right=px(0), ~bottom=px(10)),
      fontFamily("mr-eaves-xl-modern, sans-serif"),
    ]);
  let masthead =
    style([
      display(`flex),
      alignItems(center),
      height(`percent(100.)),
      textDecoration(none),
      paddingLeft(px(40)),
      color(white),
    ]);
  let links = style([display(`flex), justifyContent(flexEnd), width(vw(80.0))]);
  let link = style([paddingLeft(px(20)), color(white), textDecoration(none)]);
};

let component = ReasonReact.statelessComponent("App");
let make = (~currentSession, ~deleteSession, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  render: _self => {
    <div className=Styles.header>
      <Link href="/" className=Styles.masthead> <h1> {ReasonReact.string("Elysium")} </h1> </Link>
      <div className=Styles.links>
        ...{
             switch (currentSession) {
             | Some(_session) => [|
                 <a className=Styles.link href="#" onClick={_ => deleteSession()}>
                   <h2> {ReasonReact.string("Sign out")} </h2>
                 </a>,
                 <Link className=Styles.link href="/submit">
                   <h2> {ReasonReact.string("Submit a project")} </h2>
                 </Link>,
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
