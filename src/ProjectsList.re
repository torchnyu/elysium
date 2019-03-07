module Styles = {
  open Css;
  let projects = style([display(`flex), flexDirection(column)]);
};

open Types;

let component = ReasonReact.statelessComponent("Projects");

let make = (_children, ~projects) => {
  ...component,
  render: _self => {
    <div className=Styles.projects>
      {ReasonReact.array(
         Array.of_list(List.map(((slug, {name, color}: project)) => <Project slug name color />, projects)),
       )}
    </div>;
  },
};
