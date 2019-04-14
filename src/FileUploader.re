open Types;

[@bs.deriving abstract]
type jsProps = {
  className: string,
  resourceName: string,
  resourceId: int,
  apiUrl: string,
};

[@bs.module "./FileUploader.r"] external fileUploader: ReasonReact.reactClass = "default";

let make = (~className="", ~resourceName, ~resourceId, _children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=fileUploader,
    ~props=jsProps(~className, ~resourceName, ~resourceId, ~apiUrl=Utils.apiUrl),
    _children,
  );
