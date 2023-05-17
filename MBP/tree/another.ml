type 'a btree =
    Leaf of 'a
    | Empty
    | Node of 'a btree * 'a btree;;

let rec fold_left fn acc tree =
    match tree with
    | Leaf x     -> fn acc x
    | Empty      -> acc
    | Node(l, r) ->
        fold_left fn (fold_left fn acc l) r


let rec fold_right fn acc tree =
    match tree with
    | Leaf x     -> fn acc x
    | Empty      -> acc
    | Node(l, r) ->
        fold_right fn (fold_left fn acc r) l
            

let rec min tree =
    match tree with
    | Leaf x                -> x
    | Node(Empty, Leaf r)   -> r
    | Node(Leaf l, _)       -> l
    | Node(l, _)            -> min l

let rec delete elem tree =
    match tree with 
    | Node(l, r) -> if l = elem then
        Node(Empty, r)
        else if r = elem then
        Node(l, Empty)
        else Node(delete elem l, delete elem r) 
    | x    -> if x = elem then Empty
        else x

let rec insert elem tree = 
    match tree with
    | Node(l, r) -> if elem > min r 
        then Node(l, insert elem r)
        else Node(insert elem l, r)
    | Leaf x -> 
        if elem > x then 
            Node(Leaf x, Leaf elem)  
            else Node(Leaf elem, Leaf x)
    | Empty -> Leaf elem;;

let construct_tree lst =
    let rec fn lst tree = 
        match lst with
        | x::[]   -> insert x tree
        | x::xs -> fn xs (insert x tree)
        | []    -> Empty
    in fn lst Empty ;;

let print_tree d convert_func =
    let rec f d = 
        match d with
        | Leaf i -> "Leaf " ^ convert_func i
        | Empty -> "Empty"
        | Node(x,y) -> "Node (" ^ f x ^ ", " ^ f y ^ ")"
    in Printf.printf "%s" (f d);;

let tr1 = construct_tree [8; 4];;
let tr1 = insert 2 tr1;;

print_tree tr1 string_of_int;;
let tr_sub l r = l @ [r];;
let num = fold_left tr_sub [] tr1;;
let num = fold_right tr_sub [] tr1;;
(* let tr = construct_tree [1;2;3;4;5];;
let tr1 = delete (Leaf 1) tr1;;
print_tree tr string_of_int;; *)

(* let construct_tree lst = 
    let rec f lst acc =
        | match lst with 
        | x::[] -> Leaf x
        | x::xs -> Node(Leaf x, (f xs acc))
        | [] -> acc 
    in f lst Empty;; *)

(*
let map tree f = 
    let rec fn btree =
        match tree with
        Leaf i -> fn i
        | Empty -> Empty
        | Node(x,y) -> Node(fn x, fn y)
    in fn tree;;
*)
