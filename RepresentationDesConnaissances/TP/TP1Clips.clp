;Victorien Grude


;=============================================================================================
;Theme neutre
;=============================================================================================
(deffacts faits-initiaux
    (output "Bonjour, pouvez-vous me donner des informations ?")
    (theme neutre))



(defrule regle-bonjour
    ?fact <- (input $? beau temps $?)
    (theme neutre)
    =>
    (retract ?fact)
    (assert (output "Après le beau temps, c'est la pluie !")))
 
    
(defrule regle-connaisance
	?fact <- (input $?a est $?b)
	(theme neutre)
	=>
	(retract ?fact)
	(assert (relation $?a est $?b))
	(assert (output "Merci de cette information")))	

(defrule regle-memoire
	?fact <- (input c'est quoi $?a $?)
	(relation $?a est $?b)
	(theme neutre)
	=>
	(retract ?fact)
	(assert (output $?a est $?b je crois)))

;=============================================================================================
;Theme reves
;=============================================================================================
(defrule regle-reve-frequence 
	?fact <- (input $? souvent|parfois|tout le temps|jamais $?)
	(theme reve)
	=>
	(retract ?fact)
	(assert (output "De quoi revez vous le plus souvent ?")))
	
(defrule regle-reve-thematique
	?fact <- (input je reve de $?t)
	(theme reve)
	=>
	(retract ?fact)
	(assert (output peu de gens reve de $?t)))
	
(defrule regle-pb-sommeil
	?fact <- (input $? mal $?)
	(theme reve)
	=>
	(retract ?fact)
	(assert (output "En regle generale, avez-vous des problemes de sommeil ?")))
	
(defrule regle-sommeil-mauvais
	?fact <- (input oui)
	(theme reve)
	=>
	(retract ?fact)
	(assert (output "Pour bien dormir essayez les tisannes")))

(defrule regle-sommeil-bon
	?fact <- (input non)
	(theme reve)
	=>
	(retract ?fact)
	(assert (output "Vous devez etre en forme")))

;=============================================================================================
;Changement de theme
;=============================================================================================
(defrule regle-theme-reve-lance
	?fact <- (input $? reve|sommeil|dormir $?)
	?theme <- (theme $?)
	=>
	(retract ?fact)
	(retract ?theme)
	(assert (theme reve))
	(assert (output "Cela vous arrive-t-il souvent de faire des reves ?")))




;=============================================================================================
;Fin d'un theme
;=============================================================================================

(defrule regle-fin-theme
	?fact <- (input je ne veux plus en parler)
	?theme <- (theme $?)
	=>
	(retract ?fact)
	(retract ?theme)
	(assert (theme neutre))
	(assert (output "Ok parlons d'autre chose")))
	
	

;=============================================================================================
;Incomprehenssion
;=============================================================================================

(defrule regle-non-compris
	?fact <- (input $?)
	=>
	(retract ?fact)
	(assert(output "Je ne comprend pas ce que vous dites")))

	
;=============================================================================================
;Regle de fin de programme
;=============================================================================================
(defrule au-revoir
    ?fact <- (input $? au revoir $?)
    =>
    (retract ?fact)
    (printout t "A plus tard" crlf))

;=============================================================================================
;Regle de debut de programe
;=============================================================================================
(defrule interaction
	?fact <- (output $?a)
	=>
	(retract ?fact)
	(printout t $?a crlf)
	(assert (input (explode$ (lowcase (readline))))))