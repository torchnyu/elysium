let component = ReasonReact.statelessComponent("ProjectForm");

module SubmitProjectParams = {
  type state = {
    name: string,
    description: string,
  };
  type fields = [ | `name | `description];
  let lens = [
    (`name, s => s.name, (s, name) => {...s, name}),
    (`description, s => s.description, (s, description) => {...s, description}),
  ];
};

module SubmitProjectForm = ReForm.Create(SubmitProjectParams);

let make = _children => {
  ...component,
  render: _self => {
    <div>
      <h1> {ReasonReact.string("New Project")} </h1>
      <SubmitProjectForm
        onSubmit={({values}) => Js.log(values)}
        initialState={name: "", description: ""}
        schema=[(`name, Required)]>
        ...{({handleSubmit, handleChange, form, getErrorForField}) =>
          <form onSubmit={ReForm.Helpers.handleDomFormSubmit(handleSubmit)}>
            <label>
              {ReasonReact.string("Name: ")}
              <input value={form.values.name} onChange={ReForm.Helpers.handleDomFormChange(handleChange(`name))} />
            </label>
            <p> {getErrorForField(`name) |> Belt.Option.getWithDefault(_, "") |> ReasonReact.string} </p>
            <label>
              {ReasonReact.string("Description: ")}
              <input
                value={form.values.description}
                onChange={ReForm.Helpers.handleDomFormChange(handleChange(`description))}
              />
            </label>
            <p> {getErrorForField(`name) |> Belt.Option.getWithDefault(_, "") |> ReasonReact.string} </p>
            <button type_="submit"> {"Submit" |> ReasonReact.string} </button>
          </form>
        }
      </SubmitProjectForm>
    </div>;
  },
};
