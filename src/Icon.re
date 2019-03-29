type icons =
  | LocationPin
  | Calendar
  | Empty;

let component = ReasonReact.statelessComponent("Icon");

let make = (~className="", ~iconType, _children) => {
  ...component,
  render: _self =>
    switch (iconType) {
    | LocationPin =>
      <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" className={"icon-location-pin " ++ className}>
        <path
          className="primary"
          d="M5.64 16.36a9 9 0 1 1 12.72 0l-5.65 5.66a1 1 0 0 1-1.42 0l-5.65-5.66zM12 13a3 3 0 1 0 0-6 3 3 0 0 0 0 6z"
        />
        <path className="secondary" d="M12 1a9 9 0 0 1 6.36 15.36l-5.65 5.66a1 1 0 0 1-.71.3V13a3 3 0 0 0 0-6V1z" />
      </svg>
    | Calendar =>
      <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" className={"icon-calendar-date " ++ className}>
        <path
          className="primary"
          d="M5 4h14a2 2 0 0 1 2 2v13a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2V6c0-1.1.9-2 2-2zm0 5v10h14V9H5z"
        />
        <path
          className="secondary"
          d="M13 13h3v3h-3v-3zM7 2a1 1 0 0 1 1 1v3a1 1 0 1 1-2 0V3a1 1 0 0 1 1-1zm10 0a1 1 0 0 1 1 1v3a1 1 0 0 1-2 0V3a1 1 0 0 1 1-1z"
        />
      </svg>
    | Empty => <div> {ReasonReact.string("Icon doesn't exist!")} </div>
    },
};
