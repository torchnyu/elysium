[@bs.deriving jsConverter]
type project = {
  id: int,
  name: string,
  color: string,
  slug: string,
  description: option(string),
};
