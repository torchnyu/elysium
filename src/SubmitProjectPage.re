open Types;

type actions =
  | ProjectCreated(project)
  | PreviousPage;

type page =
  | CreateProject
  | UploadImages;

type state = {
  page,
  project: option(project),
};

[@react.component]
let make = (~session, ~addSession, ~eventSlug) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ProjectCreated(project) => {page: UploadImages, project: Some(project)}
        | PreviousPage => {...state, page: CreateProject}
        },
      {page: UploadImages, project: None},
    );
  /*
     We want to update the session cause tokens can expire, so
     when we get an authenticated response, we update the session
     token with the one it returns
   */
  let finishSubmitProject = (session, project) => {
    addSession(session);
    dispatch(ProjectCreated(project));
  };
  let endpoint = Constants.apiUrl ++ "projects/images";
  <div>
    <h1> {React.string("Submit A Project")} </h1>
    {switch (state.page, state.project) {
     | (CreateProject, _) => <CreateProjectForm eventSlug session finishSubmitProject />
     | (UploadImages, Some(project)) =>
       <FileUploader className="" endpoint resourceName="project" resourceId={project.id} />
     | (UploadImages, None) => <FileUploader className="" endpoint resourceName="project" resourceId=5 />
     }}
  </div>;
};
