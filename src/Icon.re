type icons =
  | LocationPin
  | Calendar
  | Search
  | ProjectPlaceholder
  | Empty;

[@react.component]
let make = (~className="", ~iconType) => {
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
  | ProjectPlaceholder =>
    <svg id="Layer_1" viewBox="0 0 800 800">
      <path fill="#333" d="M0 0h800v800H0z" />
      <path fill="#e6e6e6" d="M0 0h800v78.326H0z" />
      <circle cx="190.982" cy="39.874" r="23.384" fill="#22b573" />
      <circle cx="121.28" cy="39.874" r="23.384" fill="#f9da23" />
      <circle cx="52.241" cy="39.874" r="23.384" fill="#e54545" />
      <path
        className="st5"
        fill="#5BB6CE"
        d="M468 205H98c-15.4 0-28-12.6-28-28s12.6-28 28-28h370c15.4 0 28 12.6 28 28s-12.6 28-28 28z"
      />
      <path
        className="st6"
        fill="#7D52AA"
        d="M435 324H216c-15.4 0-28-12.6-28-28s12.6-28 28-28h219c15.4 0 28 12.6 28 28s-12.6 28-28 28z"
      />
      <path
        className="st7"
        fill="#D7DBE2"
        d="M644 324H535c-15.4 0-28-12.6-28-28s12.6-28 28-28h109c15.4 0 28 12.6 28 28s-12.6 28-28 28z"
      />
      <path
        className="st5"
        fill="#5BB6CE"
        d="M554 447H357c-15.4 0-28-12.6-28-28s12.6-28 28-28h197c15.4 0 28 12.6 28 28s-12.6 28-28 28z"
      />
      <path
        className="st7"
        fill="#D7DBE2"
        d="M691.46 562H452.54c-14.597 0-26.54-11.943-26.54-26.54v-2.919c0-14.597 11.943-26.54 26.54-26.54h238.92c14.597 0 26.54 11.943 26.54 26.54v2.919c0 14.597-11.943 26.54-26.54 26.54z"
      />
      <path
        className="st6"
        fill="#7D52AA"
        d="M333 689H221c-15.4 0-28-12.6-28-28s12.6-28 28-28h112c15.4 0 28 12.6 28 28s-12.6 28-28 28z"
      />
      <path
        className="st5"
        fill="#5BB6CE"
        d="M603 689H430c-15.4 0-28-12.6-28-28s12.6-28 28-28h173c15.4 0 28 12.6 28 28s-12.6 28-28 28z"
      />
    </svg>
  | Empty => <div> {React.string("Icon doesn't exist!")} </div>
  };
};
