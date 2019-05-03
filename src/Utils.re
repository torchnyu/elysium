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

let parseDateFloat = dateFloat => {
  let date = Js.Date.fromFloat(dateFloat);
  let month = monthToAbbr(Js.Date.getMonth(date));
  let day = int_of_float(Js.Date.getDay(date));
  let year = Js.Date.getFullYear(date);
  (month, day + 1, year);
};

let dateRangeToStr = (startTime, endTime) => {
  switch (startTime, endTime) {
  | (Some(startTime), Some(endTime)) =>
    let (startMonth, startDay, startYear) = parseDateFloat(startTime);
    let (endMonth, endDay, endYear) = parseDateFloat(endTime);
    /* All date strings start with this, but depending on how close the dates
       are, we elide some of the repetative details */
    let dateStringStart = startMonth ++ " " ++ string_of_int(startDay);
    if (startMonth == endMonth && startYear == endYear) {
      if (startDay == endDay) {
        dateStringStart ++ " " ++ Js.Float.toString(startYear);
      } else {
        dateStringStart ++ {js| – |js} ++ string_of_int(endDay) ++ " " ++ Js.Float.toString(startYear);
      };
    } else {
      dateStringStart
      ++ {js| – |js}
      ++ endMonth
      ++ " "
      ++ string_of_int(endDay)
      ++ " "
      ++ Js.Float.toString(startYear);
    };
  | (_, _) => "N/A"
  };
};

let apiUrl = "http://localhost:4000";
