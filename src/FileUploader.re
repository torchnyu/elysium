[@bs.deriving abstract]
type jsProps = {
  className: string,
  handleFiles: array(FileRe.t) => string,
};

[@bs.module "./FileUploader.r"] external fileUploader: ReasonReact.reactClass = "default";

let make = (~className="", ~handleFiles, _children) =>
  ReasonReact.wrapJsForReason(~reactClass=fileUploader, ~props=jsProps(~className, ~handleFiles), _children);
