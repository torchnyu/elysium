module Styles = {
  open Css;
  let projectsGrid = style([display(grid)]);
  let app =
    style([display(`flex), flexDirection(column), alignItems(center), fontFamily("Helvetica, sans-serif")]);
};

let component = ReasonReact.statelessComponent("App");

let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,

  render: _self => {
    <div className=Styles.app> <Header /> <Projects /> </div>;
  },
};
