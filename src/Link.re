let component = ReasonReact.statelessComponent("Link");

let handleClick = (location, event) =>
  if (!ReactEvent.Mouse.defaultPrevented(event)) {
    ReactEvent.Mouse.preventDefault(event);
    ReasonReact.Router.push(location);
  };

let make = (children, ~className, ~href) => {
  ...component,
  render: _self => {
    <a href ?className onClick={handleClick(href)}> ...children </a>;
  },
};
