[@bs.module "./FileUploader.r.js"] [@react.component]
external make: (~className: string, ~resourceName: string, ~resourceId: int, ~apiUrl: string) => React.element =
  "default";
