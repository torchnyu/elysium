type icons =
  | LocationPin
  | Calendar
  | Search
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
    | Search =>
      <svg height="32px" version="1.1" viewBox="0 0 32 32" width="32px" xmlns="http://www.w3.org/2000/svg">
        <title />
        <desc />
        <defs />
        <g fill="none" fillRule="evenodd" id="Page-1" stroke="none" strokeWidth="1">
          <g fill="white" id="icon-111-search">
            <path
              d="M19.4271164,21.4271164 C18.0372495,22.4174803 16.3366522,23 14.5,23 C9.80557939,23 6,19.1944206 6,14.5 C6,9.80557939 9.80557939,6 14.5,6 C19.1944206,6 23,9.80557939 23,14.5 C23,16.3366522 22.4174803,18.0372495 21.4271164,19.4271164 L27.0119176,25.0119176 C27.5621186,25.5621186 27.5575313,26.4424687 27.0117185,26.9882815 L26.9882815,27.0117185 C26.4438648,27.5561352 25.5576204,27.5576204 25.0119176,27.0119176 L19.4271164,21.4271164 L19.4271164,21.4271164 Z M14.5,21 C18.0898511,21 21,18.0898511 21,14.5 C21,10.9101489 18.0898511,8 14.5,8 C10.9101489,8 8,10.9101489 8,14.5 C8,18.0898511 10.9101489,21 14.5,21 L14.5,21 Z"
              id="search"
            />
          </g>
        </g>
      </svg>
    | Empty => <div> {ReasonReact.string("Icon doesn't exist!")} </div>
    },
};
