let component = ReasonReact.statelessComponent("ProjectForm");

let make = _children => {
  ...component,
  render: _self => {
    <div> <h1> {ReasonReact.string("New Project")} </h1> </div>;
  },
};
