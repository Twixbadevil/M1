;Grude Victorien

(deffacts fait_initiaux
	(est_poilu kangourou)
	(poche_ventrale kangourou)
	(grand-bond kangourou)
	
	(est_poilu koala)
	(poche_ventrale koala)
	(grimpe_arbre koala)

	(est_poilu chauve-souris)
	(carnivore chauve-souris)
	(vole chauve-souris)
	
	(est_poilu ornithorynque)
	(carnivore ornithorynque)
	(pond_oeuf ornithorynque)
	

	(mange_eucalyptus panda)
	(mange_eucalyptus koala)
	(mange_bambou panda))
	
(defrule donne_lait
	(est_poilu ?a)
	=>
	(assert (donne_lait ?a))
	(printout t ?a " donne du lait a ses petits" crlf))
	
(defrule est_phalanger
	(poche_ventrale ?a)
	(phalange_longue ?a)
	=>
	(assert (est_phalanger ?a))
	(printout t ?a " est un phalanger crlf"))
	
(defrule est_koala
	(est_marsupial ?a)
	(grimpe_arbre ?a)
	=>
	(assert (est_koala ?a))
	(printout t ?a " est un koala" crlf))
	
(defrule est_marsupial
	(donne_lait ?a)
	(poche_ventrale ?a)
	=>
	(assert (est_marsupial ?a))
	(printout t ?a " est un marsupial" crlf))
	
(defrule est_kangourou
	(est_marsupial ?a)
	(grand_bond ?a)
	=>
	(assert (est_kangourou ?a))
	(printout t ?a " est un kangourou" crlf))
	
(defrule est_mammifere
	(donne_lait ?a)
	=>
	(assert (est_mammifere ?a))
	(printout t ?a " est un mammifere" crlf))
	
(defrule est_koala2
	(mange_eucalyptus ?a)
	(not (mange_bambou ?a))
	=>
	(assert (est_koala ?a))
	(printout t ?a " est un koala" crlf))
	
(defrule est_chauve_souris
	(vole ?a)
	(donne_lait ?a)
	(carnivore ?a)
	=>
	(assert (est_chauve_souris ?a))
	(printout t ?a " est une chauve-souris" crlf))
	
(defrule est_faucon
	(est_oiseau ?a)
	(carnivore ?a)
	=>
	(assert (est_faucon ?a))
	(printout t ?a " est un faucon" crlf))
	
(defrule est_opossum
	(est_marsupial ?a)
	(carnivore ?a)
	(queue_prehensible ?a)
	=>
	(assert (est_opossum ?a))
	(printout t ?a " est un opossum"crlf))
	
(defrule hemisphere_sud
	(est_marsupial ?a)
	=>
	(assert (hemisphere-sud ?a))
	(printout t ?a " provient de l'hemisphere sud" crlf))
	
(defrule oiseau
	(vole ?a)
	(pond_oeuf ?a)
	=>
	(assert (oiseau ?a))
	(printout t ?a " est un oiseau" crlf))
	
(defrule est_ornithorynque
	(pond_oeuf ?a)
	(est_mammifere ?a)
	=>
	(assert (est_ornithorynque ?a))
	(printout t ?a " est un ornithorynque" crlf))