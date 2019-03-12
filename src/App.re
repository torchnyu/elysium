module Styles = {
  open Css;
  let projectsGrid = style([display(grid)]);
  let app =
    style([
      display(`flex),
      flexDirection(column),
      alignItems(center),
      fontFamily("mr-eaves-xl-modern, Helvetica, sans-serif"),
    ]);
};

open Types;
open Belt;

type routes =
  | MainPage
  | ProjectPage(string)
  | NotFoundPage
  | SubmitProjectPage
  | LoginPage;

type state = {
  currentPage: routes,
  currentSession: option(session),
  watcherID: ref(option(ReasonReact.Router.watcherID)),
};

type action =
  | GoTo(routes)
  | CreateSession(session)
  | DeleteSession;

let component = ReasonReact.reducerComponent("App");

let urlToPage = (url: ReasonReact.Router.url, session: option(session)) =>
  switch (url.path) {
  | ["projects", slug] => ProjectPage(slug)
  | ["submit"] =>
    switch (session) {
    | None =>
      ReasonReact.Router.push("/login");
      LoginPage;
    | Some(_) => SubmitProjectPage
    }
  | ["login"] =>
    switch (session) {
    | None => LoginPage
    | Some(_) =>
      ReasonReact.Router.push("/");
      MainPage;
    }
  | [] => MainPage
  | _ => NotFoundPage
  };

[@bs.val] external unsafeJsonParse: string => 'a = "JSON.parse";

let createSession = (self, session) => {
  self.ReasonReact.send(CreateSession(session));
  switch (Js.Json.stringifyAny(session)) {
  | Some(stringifiedSession) => Dom.Storage.(localStorage |> setItem("session", stringifiedSession))
  | None => ()
  };
};

let deleteSession = (self, ()) => {
  self.ReasonReact.send(DeleteSession);
  Dom.Storage.(localStorage |> removeItem("session"));
};

/* Functors are cool. Option.map takes in an optional value, a and a function f, a -> b
   then returns either Some(f(a)) if a is a value or None if a is None
   */
let rehydrateSession = () => Option.map(Dom.Storage.(localStorage |> getItem("session")), unsafeJsonParse);

let make = _children => {
  ...component,
  initialState: () => {
    let currentSession = rehydrateSession();
    {
      currentPage: urlToPage(ReasonReact.Router.dangerouslyGetInitialUrl(), currentSession),
      watcherID: ref(None),
      currentSession,
    };
  },
  reducer: (action, state) =>
    switch (action) {
    | GoTo(page) => ReasonReact.Update({...state, currentPage: page})
    | CreateSession(session) => ReasonReact.Update({...state, currentSession: Some(session)})
    | DeleteSession => ReasonReact.Update({...state, currentSession: None})
    },
  didMount: self => {
    let watcherID = ReasonReact.Router.watchUrl(url => self.send(GoTo(urlToPage(url, self.state.currentSession))));
    self.state.watcherID := Some(watcherID);
    ();
  },
  willUnmount: self =>
    switch (self.state.watcherID^) {
    | Some(id) => ReasonReact.Router.unwatchUrl(id)
    | None => ()
    },
  render: self => {
    <div className=Styles.app>
      <Header deleteSession={deleteSession(self)} currentSession={self.state.currentSession} />
      {switch (self.state.currentPage) {
       | MainPage => <ProjectsList />
       | ProjectPage(slug) => <ProjectPage slug />
       | SubmitProjectPage =>
         <SubmitProjectPage createSession={createSession(self)} session={self.state.currentSession} />
       | LoginPage => <LoginPage createSession={createSession(self)} />
       | NotFoundPage => <div> {ReasonReact.string("Page not found")} </div>
       }}
    </div>;
  },
};
