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
  | OrganizerPage
  | EventPage(string)
  | LoginPage;

/*
   The app state. We have the loading state, the current page and the session.
   watcherID is the only weird one. This is so that we can remove the watcher on
   ReasonReactRouter when the component unmounts. It's a ref because we need
   mutability
 */
type state = {
  isLoading: bool,
  currentPage: page,
  currentSession: option(session),
};

type action =
  | GoTo(page)
  | CreateSession(session)
  | DeleteSession;

/*
   I suppose we should prevent any project from being called submit
 */
let urlToPage = (url: ReasonReactRouter.url) =>
  switch (url.path) {
  | ["login"] => LoginPage
  | ["register"] => RegisterPage
  | ["organizers"] => OrganizerPage
  | [eventSlug] => EventPage(eventSlug)
  | [eventSlug, "submit"] => SubmitProjectPage(eventSlug)
  | [eventSlug, slug] => ProjectPage(eventSlug, slug)
  | [] => HomePage
  | _ => NotFoundPage
  };

[@bs.val] external unsafeJsonParse: string => 'a = "JSON.parse";

let addSession = (dispatch, session) => {
  dispatch(CreateSession(session));
  switch (Js.Json.stringifyAny(session)) {
  | Some(stringifiedSession) => Dom.Storage.(localStorage |> setItem("session", stringifiedSession))
  | None => ()
  };
};

let deleteSession = (dispatch, ()) => {
  dispatch(DeleteSession);
  Dom.Storage.(localStorage |> removeItem("session"));
};

/* Functors are cool. Option.map takes in an optional value, a and a function f, a -> b
   then returns either Some(f(a)) if a is a value or None if a is None

   Basically
   Option.map :: m a -> (a -> b) -> m b
   */
let rehydrateSession = () => Option.map(Dom.Storage.(localStorage |> getItem("session")), unsafeJsonParse);

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | GoTo(page) => {...state, currentPage: page}
        | CreateSession(session) => {...state, currentSession: Some(session)}
        | DeleteSession => {...state, currentSession: None}
        },
      {
        isLoading: false,
        currentPage: urlToPage(ReasonReactRouter.dangerouslyGetInitialUrl()),
        currentSession: rehydrateSession(),
      },
    );

  React.useEffect0(() => {
    let watcherID = ReasonReactRouter.watchUrl(url => dispatch(GoTo(urlToPage(url))));
    Some(() => ReasonReactRouter.unwatchUrl(watcherID));
  });
  if (state.isLoading) {
    <div className=Styles.app> <h1> {React.string("Loading")} </h1> </div>;
  } else {
    <div className=Styles.app>
      <Header
        isHome={state.currentPage == HomePage}
        deleteSession={deleteSession(dispatch)}
        currentSession={state.currentSession}
      />
      {switch (state.currentPage, state.currentSession) {
       | (HomePage, _) => <HomePage />
       | (ProjectPage(eventSlug, slug), _) => <ProjectPage slug eventSlug />
       | (SubmitProjectPage(eventSlug), Some(session)) =>
         <SubmitProjectPage eventSlug addSession={addSession(dispatch)} session={Some(session)} />
       | (SubmitProjectPage(_), None) =>
         ReasonReactRouter.push("/login");
         <div> {React.string("Redirecting to login...")} </div>;
       | (LoginPage, None) => <LoginPage addSession={addSession(dispatch)} />
       | (LoginPage, Some(_session))
       | (RegisterPage, Some(_session)) =>
         ReasonReactRouter.push("/");
         <div> {React.string("Redirecting back home")} </div>;
       | (RegisterPage, None) => <RegisterPage addSession={addSession(dispatch)} />
       | (EventPage(slug), _) => <EventPage slug />
       | (OrganizerPage, _) => <OrganizerPage />
       | (NotFoundPage, _) => <div> {React.string("Page not found")} </div>
       }}
    </div>;
  };
};
