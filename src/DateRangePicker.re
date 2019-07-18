open MomentRe;
type dates = {
  startDate: Moment.t,
  endDate: Moment.t,
};
type onDatesChangeType = dates => unit;

[@bs.module "./DateRangePicker.r.js"] [@react.component]
external make: (~startDate: Moment.t, ~endDate: Moment.t, ~onDatesChange: onDatesChangeType) => React.element =
  "default";
