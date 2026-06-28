# Plantillas

```CLIPS
;; Plantilas usadas por el sistema
(deftemplate laboratorio
	(slot nombre)
	(slot capacidad (type INTEGER))
	(slot ocupadas (type INTEGER))
)

(deftemplate solicitud
	(slot estudiante)
	(slot tipo
		(allowed-symbols grado master doctorado))
	(slot lab)
)

(deftemplate estado-solicitud
	(slot estudiante)
	(slot lab)
	(slot estado (allowed-symbols pendiente aceptada espera          rechazada))
)

(deftemplate informe
	(slot solicitudes-espera (type INTEGER))
)
```

# Hechos iniciales

```CLIPS
(deffacts initial-facts
	(laboratorio (nombre IA) (capacidad 2) (ocupadas 0))
	(solicitud (estudiante ana) (tipo doctorado) (lab IA))
	(solicitud (estudiante luis) (tipo master) (lab IA))
	(solicitud (estudiante carla) (tipo grado) (lab IA))
	
	;; No hay solicitudes pendientes tdv
	(informe (solicitudes-espera 0))
)
```
# Reglas para cubrir el funcionamiento del sistema

```CLIPS
;; Estado de solicitud inicial
(defrule estado-inicial-solicitud
	(declare (salience 200))
	(solicitud (estudiante ?e) (lab ?lab))
	(not (estado-solicitud (estudiante ?e) (lab ?lab)))
	=>
	(assert (estado-solicitud (estudiante ?e) (lab ?lab)            (estado pendiente)))
	(printout t "Estado init: " ?e ": pendiente" crlf)
)

;; Rechazo por laboratorio inexistente
(defrule rechazo-lab-inexistente
	(declare (salience 100))
	(solicitud (estudiante ?e) (lab ?lab))
	?est <- (estado-solicitud
	(estudiante ?e) (lab ?lab) (estado pendiente))
	(not (laboratorio ?lab))
	=>
	(modify ?est (estado rechazada))
	(printout t "Solicitud rechazada: el laboratorio " ?lab no      existe. Estudiante: " ?e crlf)
)

;; Aceptación según prioridad académica
(defrule aceptar-doctorado
	(declare (salience 30))
	(solicitud (estudiante ?e) (tipo doctorado) (lab ?lab))
	?est <- (estado-solicitud
	(estudiante ?e) (lab ?lab) (estado pendiente))
	?l <- (laboratorio (nombre ?lab) (capacidad ?cap)               (ocupadas ?ocu:(< ?ocu ?cap)))
	=>
	(modify ?est (estado aceptada))
	(modify ?l (ocupadas (+ ?ocu 1)))
	(printout t "Solicitud aceptada: " ?e "de doctorado accede       al laboratorio" ?lab crlf)
)

(defrule aceptar-master
	(declare (salience 20))
	(solicitud (estudiante ?e) (tipo master) (lab ?lab))
	?est <- (estado-solicitud
	(estudiante ?e) (lab ?lab) (estado pendiente))
	?l <- (laboratorio (nombre ?lab) (capacidad ?cap)               (ocupadas ?ocu:(< ?ocu ?cap)))
	=>
	(modify ?est (estado aceptada))
	(modify ?l (ocupadas (+ ?ocu 1)))
	(printout t "Solicitud aceptada: " ?e "de master accede          al laboratorio" ?lab crlf)
)

(defrule aceptar-grado
	(declare (salience 10))
	(solicitud (estudiante ?e) (tipo grado) (lab ?lab))
	?est <- (estado-solicitud
	(estudiante ?e) (lab ?lab) (estado pendiente))
	?l <- (laboratorio (nombre ?lab) (capacidad ?cap)               (ocupadas ?ocu:(< ?ocu ?cap)))
	=>
	(modify ?est (estado aceptada))
	(modify ?l (ocupadas (+ ?ocu 1)))
	(printout t "Solicitud aceptada: " ?e "de grado accede           al laboratorio" ?lab crlf)
)

;; Espera por lab lleno
(defrule enviar-espera-si-lab-lleno
	(declare (salience 5))
	(solicitud (estudiante ?e) (lab ?lab))
	?est <- (estado-solicitud (estudiante ?e) (lab ?lab)            (estado pendiente))
	(laboratorio (nombre ?lab) (capacidad ?cap)                      (ocupadas ?ocu&:(>= ?ocu ?cap)))
	=>
	(modify ?est (estado espera))
	(printout t "Solicitud en espera: " ?e "para el lab" ?lab       crlf)
)

; Actualizar contador espera
; Cada vez que una solicitud pasa al estado espera, se aumenta
(defrule contador-espera-increment
	?est <- (estado-solicitud (estado espera))
	?inf <- (informe (solicitudes-espera ?n))
	(not (contada-espera ?est))
	=>
	(modify ?inf (solicitudes-espera (+ ?n 1)))
	(assert (contada-espera ?est))	
)
```
# Informe final

```CLIPS
(defrule informe-final-solicitudes-espera
	(declare (salience -10))
	(not (estado-solicitud (estado pendiente)))
	
	(informe (solicitudes-espera ?n))
	
	(printout t crlf "INFORME FINAL" crlf "Sols en espera:" ?n      crlf)
)
```