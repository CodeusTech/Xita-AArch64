(*
  functions.xs
  Codeus Tech
  Authored on   October 30, 2019
  Last Modified October 30, 2019
*)

(*
  Contains test-case file for XCS Function Testing
*)



(*
  Declarations
*)

let five = 5;;
let sum x y = x + y;;
let sum x y z = x + y + z;;
let prod x y = y * x


(*
  Invocations
*)

--five             --  Primitive Function Testing
(*
(sum 1 2);;      --  Parameterized Function Testing
(sum 1 2 3);;    --  Overloaded Function Testing
(prod 1 2) + five;; --  Test Functions as Expressions



--  Test Nested Functions

debug "Test Unparameterized Functions"
let test = 
    1


*)

