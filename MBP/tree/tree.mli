type 'a btree =
    Leaf of 'a
    | Empty
    | Node of 'a btree * 'a btree;;

val construct_tree : 'a list -> 'b btree
val print_tree : 'a btree -> ('a -> string) -> 'b btree
(*
val map : ('a -> 'b) -> 'a btree -> 'b btree
val sum : ('a -> 'a -> 'a) -> 'a -> 'a btree -> 'a
val fold_left : ('a -> 'b -> 'a) -> 'a -> 'a btree -> 'a
val fold_right: ('a -> 'b -> 'a) -> 'a -> 'a btree -> 'a
val mount : 'a btree -> 'a btree -> 'a -> ('a -> 'a -> bool)

val delete...
val insert...
val merge ...
*)
