module Styles = {
  open Css;
  let project =
    style([
      display(`flex),
      flexDirection(column),
      alignItems(center),
      justifyContent(center),
      minWidth(vw(90.0)),
      color(hex("232c33")),
    ]);
};
let component = ReasonReact.statelessComponent("ProjectPage");

open Types;

let make = (_children, ~project: project) => {
  ...component,
  render: _self => {
    <div className=Styles.project>
      <h1> {ReasonReact.string(project.name)} </h1>
      <p> {ReasonReact.string(project.description)} </p>
    </div>;
  },
};
