exception InvalidMonth(float);

let monthToAbbr = month =>
  switch (month) {
  | 0. => "Jan"
  | 1. => "Feb"
  | 2. => "Mar"
  | 3. => "Apr"
  | 4. => "May"
  | 5. => "Jun"
  | 6. => "Jul"
  | m => raise(InvalidMonth(m))
  };

let dateFloatToAbbr = dateFloat => {
  let date = Js.Date.fromFloat(dateFloat);
  let month = monthToAbbr(Js.Date.getMonth(date));
  let day = int_of_float(Js.Date.getDay(date));
  month ++ " " ++ string_of_int(day + 1);
};

let getYear = dateFloat => {
  let date = Js.Date.fromFloat(dateFloat);
  string_of_float(Js.Date.getFullYear(date));
};
