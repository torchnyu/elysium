module Styles = {
  open Css;
  let projectsGrid = style([display(grid)]);
  let app = style([display(`flex), flexDirection(column), alignItems(center), fontFamily(Theme.sansSerif)]);
};

open Types;
open Belt;

/*
   The various pages for the app. We associate these with the actual urls with
   the function urlToPage
 */
type page =
  | HomePage
  | ProjectPage(string, string)
  | NotFoundPage
  | SubmitProjectPage(string)
  | RegisterPage
  | EventPage(string)
  | LoginPage;

/*
   The app state. We have the loading state, the current page and the session.
   watcherID is the only weird one. This is so that we can remove the watcher on
   ReasonReact.Router when the component unmounts. It's a ref because we need
   mutability
 */
type state = {
  isLoading: bool,
  currentPage: page,
  currentSession: option(session),
  watcherID: ref(option(ReasonReact.Router.watcherID)),
};

type action =
  | GoTo(page)
  | CreateSession(session)
  | DeleteSession;

let component = ReasonReact.reducerComponent("App");

/*
   I suppose we should prevent any project from being called submit
 */
let urlToPage = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | ["login"] => LoginPage
  | ["register"] => RegisterPage
  | [eventSlug] => EventPage(eventSlug)
  | [eventSlug, "submit"] => SubmitProjectPage(eventSlug)
  | [eventSlug, slug] => ProjectPage(eventSlug, slug)
  | [] => HomePage
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
    isLoading: false,
    currentPage: urlToPage(ReasonReact.Router.dangerouslyGetInitialUrl()),
    watcherID: ref(None),
    currentSession: rehydrateSession(),
  },
  reducer: (action, state) =>
    switch (action) {
    | GoTo(page) => ReasonReact.Update({...state, currentPage: page})
    | CreateSession(session) => ReasonReact.Update({...state, currentSession: Some(session)})
    | DeleteSession => ReasonReact.Update({...state, currentSession: None})
    },
  didMount: self => {
    let watcherID = ReasonReact.Router.watchUrl(url => self.send(GoTo(urlToPage(url))));
    self.state.watcherID := Some(watcherID);
    ();
  },
  willUnmount: self =>
    switch (self.state.watcherID^) {
    | Some(id) => ReasonReact.Router.unwatchUrl(id)
    | None => ()
    },
  render: self =>
    if (self.state.isLoading) {
      <div className=Styles.app> <h1> {ReasonReact.string("Loading")} </h1> </div>;
    } else {
      <div className=Styles.app>
        <Header
          isHome={self.state.currentPage == HomePage}
          deleteSession={deleteSession(self)}
          currentSession={self.state.currentSession}
        />
        {switch (self.state.currentPage, self.state.currentSession) {
         | (HomePage, _) => <HomePage />
         | (ProjectPage(eventSlug, slug), _) => <ProjectPage slug eventSlug />
         | (SubmitProjectPage(eventSlug), Some(session)) =>
           <SubmitProjectPage eventSlug createSession={createSession(self)} session={Some(session)} />
         | (SubmitProjectPage(_), None) =>
           ReasonReact.Router.push("/login");
           <LoginPage createSession={createSession(self)} />;
         | (LoginPage, None) => <LoginPage createSession={createSession(self)} />
         | (LoginPage, Some(_session))
         | (RegisterPage, Some(_session)) =>
           ReasonReact.Router.push("/");
           <HomePage />;
         | (RegisterPage, None) => <RegisterPage createSession={createSession(self)} />
         | (EventPage(slug), _) => <EventPage slug />
         | (NotFoundPage, _) => <div> {ReasonReact.string("Page not found")} </div>
         }}
      </div>;
    },
};
