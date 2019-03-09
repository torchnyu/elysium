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

let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,

  render: _self => {
    <div className=Styles.header>
      <Link href="/" className=None> <h1> {ReasonReact.string("Elysium")} </h1> </Link>
      <Link href="/submit" className=None> <h2> {ReasonReact.string("Submit a project")} </h2> </Link>
    </div>;
  },
};
