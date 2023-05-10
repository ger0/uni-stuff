type 'a btree =
    Leaf of 'a
    | Empty
    | Node of 'a btree * 'a btree;;

let construct_tree list = 
    let rec f list acc =
        match list with 
        head::tail -> Node(Leaf head, (f tail Empty))
        | [] -> acc 
    in list Empty;;

let print_tree d string_of_leaf =
    let rec f d = 
        match d with
        Leaf i -> "Leaf " ^ string_of_leaf i
        | Empty -> "Empty"
        | Node(x,y) -> "Node (" ^ f x ^ ", " ^ f y ^ ")"
    in Printf.printf "%s" (f d);;

(*
let map tree f = 
    let rec fn btree =
        match tree with
        Leaf i -> fn i
        | Empty -> Empty
        | Node(x,y) -> Node(fn x, fn y)
    in fn tree;;
*)
