type 'a btree =
    Leaf of 'a
    | Empty
    | Node of 'a btree * 'a btree;;

let rec insert elem tree = 
    match tree with
    | Node(Node l, Node r) -> 
    | Node(Leaf l, Leaf r) -> if elem > r 
        then insert elem (Leaf r)  
        else insert elem (Leaf l)
    | Leaf x -> 
        if elem > x then 
            Node(Leaf x, Leaf elem)  
            else Node(Leaf elem, Leaf x)

let construct_tree lst = 
    let rec f lst acc =
        match lst with 
        | x::[] -> Leaf x
        | x::xs -> Node(Leaf x, (f xs acc))
        | [] -> acc 
    in f lst Empty;;

let print_tree d convert_func =
    let rec f d = 
        match d with
        Leaf i -> "Leaf " ^ convert_func i
        | Empty -> "Empty"
        | Node(x,y) -> "Node (" ^ f x ^ ", " ^ f y ^ ")"
    in Printf.printf "%s" (f d);;

let tr = construct_tree [2;3];;
let tr = insert 1 tr;;
print_tree tr string_of_int;;

(*
let map tree f = 
    let rec fn btree =
        match tree with
        Leaf i -> fn i
        | Empty -> Empty
        | Node(x,y) -> Node(fn x, fn y)
    in fn tree;;
*)
