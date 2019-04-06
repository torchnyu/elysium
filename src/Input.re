module Styles = {
  open Css;
  let input = style([display(`flex), flexDirection(column), margin(px(10))]);
  let textField = style([padding(px(5)), fontSize(rem(1.3))]);
  let label = style([width(px(100))]);
  let error = style([color(red)]);
  let inputWrapper = style([display(`flex), alignItems(center)]);
};

let component = ReasonReact.statelessComponent("Input");

let make = (~value, ~onChange, ~className="", ~label="", ~type_="", ~error=None, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.input>
      <div className=Styles.inputWrapper>
        <label className=Styles.label> {ReasonReact.string(label)} </label>
        <input value onChange type_ className={className ++ " " ++ Styles.textField} />
      </div>
      {switch (error) {
       | Some(error) => <div className=Styles.error> {ReasonReact.string(error)} </div>
       | None => ReasonReact.null
       }}
    </div>,
};
