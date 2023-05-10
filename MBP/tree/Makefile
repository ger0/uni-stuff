all: pr_tree

tree.cmi: tree.mli
	ocamlc -c tree.mli

tree.cmo: tree.ml tree.cmi
	ocamlc -c tree.ml
    
pr_tree: tree.cmi tree.cmo
	ocamlc -o pr_tree tree.cmo pr_tree.ml

clean: 
	rm -r *.cmo *.cmi pr_tree
