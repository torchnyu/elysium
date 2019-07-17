[@react.component];
let make = (~className="", ~href, ~children) => {
  let handleClick = event => {
    ReactEvent.Mouse.preventDefault(event);
    ReasonReactRouter.push(href);
  };
  <a href className onClick=handleClick> children </a>;
};
