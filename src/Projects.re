module Styles = {
  open Css;
  let projects = style([display(`flex), flexDirection(column)]);
};

let component = ReasonReact.statelessComponent("Projects");

let projects = ["Aletheia", "Saber", "Website", "Org Site", "Stuyspec", "Greedux"];

let make = _children => {
  ...component,
  render: _self => {
    <div className=Styles.projects>
      {ReasonReact.array(Array.of_list(List.map(title => <Project title />, projects)))}
    </div>;
  },
};
