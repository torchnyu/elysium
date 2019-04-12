[@bs.deriving abstract]
type jsProps = {
  className: string,
  handleFiles: array(Js.t(string)) => unit,
};

[@bs.module "./FileUploader.r"] external fileUploader: ReasonReact.reactClass = "default";

let make = (~className="", ~handleFiles, _children) =>
  ReasonReact.wrapJsForReason(~reactClass=fileUploader, ~props=jsProps(~className, ~handleFiles), _children);
