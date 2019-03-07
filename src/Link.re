let component = ReasonReact.statelessComponent("Link");

let handleClick = (location, event) =>
  if (!ReactEvent.Mouse.defaultPrevented(event)) {
    ReactEvent.Mouse.preventDefault(event);
    ReasonReact.Router.push(location);
  };

let make = (children, ~href, ~className) => {
  ...component,
  render: _self => {
    <a className href onClick={handleClick(href)}> ...children </a>;
  },
};
