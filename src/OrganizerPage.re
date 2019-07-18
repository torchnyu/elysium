open MomentRe;

module StateLenses = [%lenses
  type state = {
    name: string,
    description: string,
    startDate: Moment.t,
    endDate: Moment.t,
    slug: string,
  }
];

module CreateEventForm = ReFormNext.Make(StateLenses);

[@react.component]
let make = () => {
  let {state, submit, getFieldState, handleChange}: CreateEventForm.api =
    CreateEventForm.use(
      ~schema={
        CreateEventForm.Validation.Schema([|
          Custom(Name, values => values.name == "" ? Error("We need a name for this event") : Valid),
          Custom(Description, values => values.description == "" ? Error("Description cannot be empty") : Valid),
        |]);
      },
      ~onSubmit=
        ({state}) => {
          Js.log(state);
          None;
        },
      ~initialState={name: "", description: "", startDate: momentNow(), endDate: momentNow(), slug: ""},
      (),
    );
  <div>
    <h1> {React.string("Organize an Event")} </h1>
    <form>
      <DateRangePicker
        startDate={momentNow()}
        endDate={momentNow()}
        onDatesChange={({startDate, endDate}) => {
          handleChange(StartDate, startDate);
          handleChange(EndDate, endDate);
        }}
      />
    </form>
  </div>;
};
