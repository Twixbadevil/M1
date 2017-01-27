;Grude Victorien

(deftemplate regle "Le modèle des règles de déduction"

    (multislot cond1 (type SYMBOL))    ; Première condition
    (multislot cond2 (type SYMBOL))    ; Deuxième condition (eventuellement vide)
    (multislot cond3 (type SYMBOL))    ; Troisième condition (eventuellement vide)
    (multislot alors (type SYMBOL)))   ; Conséquence



(deffacts faits_initiaux

	(propriete est_poilu kangourou)
	(propriete poche_ventrale kangourou)
	(propriete grand_bond kangourou)


	(propriete est_poilu koala)
	(propriete poche_ventrale koala)
	(propriete grimpe_arbre koala)


	(propriete est_poilu chauve_souris)
	(propriete carnivore chauve_souris)
	(propriete vole chauve_souris)

	(propriete est_poilu ornithorynque)
	(propriete carnivore ornithorynque)
	(propriete pond_oeuf ornithorynque)


	(propriete mange_eucalyptus panda)
	(propriete mange_eucalyptus koala)
	(propriete mange_bambou panda)

	(regle 
		(cond1 est_poilu)
		(alors donne_lait))
	(regle 
		(cond1 poche_ventrale) 
		(cond2 phalange_longue) 
		(alors est_phalanger))
	(regle 
		(cond1 est_marsupial) 
		(cond2 grimpe_arbre) 
		(alors est_koala))
	(regle 
		(cond1 donne_lait) 
		(cond2 poche_ventrale) 
		(alors est_marsupial))
	(regle 
		(cond1 est_marsupial) 
		(cond2 grand_bond) 
		(alors est_kangourou))
	(regle 
		(cond1 donne_lait) 
		(alors est_mammifere))
	(regle 
		(cond1 mange_eucalyptus) 
		(alors koala))
	(regle 
		(cond1 vole) 
		(cond2 est_carnivore)
		(cond3 donne_lait)
		(alors est_chauve_souris))
	(regle 
		(cond1 est_oiseau) 
		(cond2 est_carnivore) 
		(alors est_faucon))
	(regle 
		(cond1 est_marsupial) 
		(cond2 est_carnivore)  
		(cond3 queue_prehensible)  
		(alors est_opossum))
	(regle 
		(cond1 est_marsupial) 
		(alors hemisphere_sud))
	(regle 
		(cond1 vole)
		(cond2 pond_oeuf) 
		(alors est_oiseau))
	(regle 
		(cond1 est_mammifere) 
		(cond2 pond_oeuf) 
		(alors est_ornithorynque)))

(defrule condition3
	(regle (cond1 ?a) (cond2 ?b) (cond3 ?c) (alors ?d))
	(propriete ?a ?animal)
	(propriete ?b ?animal)
	(propriete ?c ?animal)
	=>
	(assert(propriete ?d ?animal))
	(printout t "(3 conditions) " ?animal " --> " ?d crlf))

(defrule condition2
	(regle (cond1 ?a) (cond2 ?b) (cond3) (alors ?d))
	(propriete ?a ?animal)
	(propriete ?b ?animal)
	=>
	(assert(propriete ?d ?animal))
	(printout t "(2 conditions) " ?animal " --> " ?d crlf))

(defrule condition1
	(regle (cond1 ?a) (cond2) (cond3) (alors ?d))
	(propriete ?a ?animal)
	=>
	(assert(propriete ?d ?animal))
	(printout t "(1 condition) " ?animal " --> " ?d crlf))