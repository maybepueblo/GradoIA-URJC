## 1. El "Taller": Herramientas de desarrollo
En nuestro [[Tema 1 - Grafos de conocimiento]] aprendimos a escribir código RDF a mano (con Turtle). Pero en el mundo real, si tienes millones de datos, no lo haces a mano. Usas **Frameworks** (programadores) y **Editores** (diseñadores). 
### A. Frameworks (programmer focused)
Son librerías de código que te permiten crear aplicaciones que "hablan" Web Semántica. Son cajas de herramientas para construir sin tener que fabricar tú mismo todo.

| Herramienta     | Lenguaje | Uso                                                                                                    |
| --------------- | -------- | ------------------------------------------------------------------------------------------------------ |
| **RDFLib**      | Python   | Fácil de usar para leer, escribir y consultar grafos pequeños o medianos.                              |
| **Apache Jena** | Java     | Incluye su propia base de datos (TDB) y un motor muy potente para hacer consultas SPARQL (llamado ARQ) |
| **OWL API**     | Java     | Especializada en lógica compleja (OWL). Usada cuando quieres hacer razonamiento complicado             |
| **RDF4J**       | Java     | Framework modular estándar para manejar bases de datos RDF.                                            |

### B. Editores de Ontologías (human focused)
En vez de programar, existen interfaces gráficas (ventanas, menús). Usamos un editor.
- **Protégé:** Estándar mundial. Permite dibujar las clases, las fechas y las reglas sin escribir una sola línea de código.
	- *Uso*: Crear ontologías, comprobar si tienen errores lógicos (consistencia) y exportarlas a OWL/Turtle
## 2. Linked Data (Web de Datos)
Aquí se hace global. Tim Berners-Lee definió los 4 **Principios de Linked Data** para publicar datos en la web. Si cumples esto, tus datos son perfectos.

Los 4 Mandamientos:
1. **Usar URIs como nombre:** Todo debe tener un identificador único (como un DNI web). No vale decir "Madrid", hay que decir `http://dbpedia.org/resource/Madrid`.
2. **Usar HTTP:** Esas URIs deben ser direcciones web reales. Si yo pego esa dirección en mi navegador, tengo que encontrar algo.
3. **Usar estándares (RDF/SPARQL):** Cuando alguien visite esa dirección, la información debe estar en un formato útil (RDF), no solo en texto plano.
4. **Incluir Enlaces:** Los datos deben apuntar a los datos de otras personas.
	- *Ejemplo*: Una base de datos "Profesores" debe tener un enlace a la base de datos de "Universidades"de la DBpedia. Así se crea la red gigante.
### Razonadores ontológicos
Aplicadores de lógica descriptiva sobre ontologías RDF/OWL para derivar conocimiento implícito.

**Importancia**
- Detectan inconsistencias en ontologías
- Permiten clasificar automáticamente jerarquías de clases
- Ayudan a descubrir relaciones ocultas entre individuos o clases

**Usos**
- Validar ontologías mientras se construyen
- Apoyo a sistemas inteligentes (apoyadores, asistentes semánticos)
- Investigación biomédica (verificación de coherencia en ontologías médicas)
- Industria (garantizar integridad en catálogos de productos o servicios)

**Ejemplos principales**
- **ELK** Especializado en OWL EL, rápido y escalable
- **Pellet** Soporta OWL DL y OWL 2 
- **HermiT** Basado en tableaux, preciso para OWL 2
### Vocabularios
Conjuntos de términos estandarizados para describir recursos en RDF.

**Principales vocabularios**
- **Schema.org** - Vocabulario para describir entidades del mundo real 
- **VCard** - Información de contacto de personas y organizaciones
- **GeoNames** - Base de datos geográfica colaborativa
- **GoodRelations** - Específico para comercio electrónico y marketing
- **DOAP (Description of a Project)** - Para describir proyectos software
- **FOAF (Friend of a Friend)** - Describir personas, relaciones e intereses
- **Dublin Core** - Estándar de metadatos para describir cualquier tipo de recurso
#### Schema.org
Creado en 2011 por Google, Bing, Yahoo! y Yandex para unificar vocabularios web.
**Características**:
- URI base: https://schema.org/
- Define cientos de clases y miles de propiedades
- ORganizado como core + extensiones
- Usado en e-commerce, recetas, eventos, artículos, negocios locales
- Permite a los buscadores generar rich snippets
- Base de muchos Knowledge Graphs
**Ejemplo de uso en JSON-LD**
```JSON
<script type="application/ld+json">
{
  "@context": "https://schema.org",
  "@type": "Restaurant",
  "name": "Pizzería Sabores",
  "address": {
    "@type": "PostalAddress",
    "streetAddress": "Calle Mayor 10",
    "addressLocality": "Madrid",
    "addressCountry": "España"
  },
  "servesCuisine": "Pizza",
  "telephone": "+34-910-111-222",
  "url": "http://pizzeriasabores.example.com",
  "priceRange": "$$"
}
</script>
```
#### VCard
Vocabulario RDF basado en estándar de tarjetas de contacto electrónicas

**Define:**
- Clases: `vcard:Individual`, `vcard:Organization
- Propiedades: `vcard:fn`, `vcard:hasEmail`, `vcard:hasTelephone`
- URI base https://www.w3.org/2006/vcard/ns#

**Usos**
- Representar información de contacto legible por máquinas
- Facilitar interoperabilidad entre sistemas
- Directorios en línea, perfiles personales, datos institucionales

**Ejemplo en turtle**
```turtle
@prefix vcard: <http://www.w3.org/2006/vcard/ns#> .
<#JuanPerez> a vcard:Individual ;
  vcard:fn "Juan Pérez" ;
  vcard:hasEmail <mailto:juan.perez@example.org> ;
  vcard:hasTelephone <tel:+34-600-123-456> ;
  vcard:hasAddress [
    a vcard:Home ;
    vcard:street-address "Calle Mayor 10" ;
    vcard:locality "Madrid" ;
    vcard:country-name "España"
  ] .
```
#### GeoNames
Base de datos geográfica colaborativa y gratuita con más de 11 millones de lugares
**Características**
- Cada lugar - URI único
- Datos en RDF, XML, JSON, etc
- Compatible con Linked Data
- Ofrece servicio web y APIs para búsqueda de lugares, coordenadas, códigos postales, etc.
**Ejemplo en RDF**
```turtle
@prefix gn: <http://www.geonames.org/ontology#> .
@prefix geo: <http://www.w3.org/2003/01/geo/wgs84_pos#> .
<http://sws.geonames.org/3117735/> a gn:Feature ;
  gn:name "Madrid"@es ;
  gn:countryCode "ES" ;
  gn:population "3266126" ;
  geo:lat "40.4167" ;
  geo:long "-3.7033" .
```
#### GoodRelations
Vocabulario RDF/OWL para comercio electrónico y marketing
**Clases y propiedades clave**
- `gr:BusinessEntity`, `gr:ProductOrService`, `gr:Offering`
- `gr:hasPriceSpecification`, `gr:availableAtOrFrom`, `gr:validThrough`
- compatible con schema.org
**Ejemplo de uso**
```turtle
@prefix gr: <http://purl.org/goodrelations/v1#> .
:TiendaSabores a gr:BusinessEntity ;
  gr:legalName "Pizzería Sabores, S.L."@es ;
  gr:hasURL <http://pizzeriasabores.example.com> .
```
#### DOAP (Description of a Project)
Vocabulario para describir proyectos software
**Elementos principales:**
- `doap:Project`, `doap:name`, `doap:description`, `doap:homepage`
- `doap:repository`, `doap:programming-language`, `doap:release`
- `doap:maintainer`, `doap:license`, `doap:category`
**Ejemplo**
```turtle
@prefix doap: <http://usefulinc.com/ns/doap#> .
:MiApp a doap:Project ;
  doap:name "MiApp" ;
  doap:description "Aplicación de ejemplo para gestionar tareas personales."@es ;
  doap:homepage <http://miapp.example.org> ;
  doap:programming-language "Python" ;
  doap:license <http://opensource.org/licenses/MIT> ;
  doap:repository [ a doap:GitRepository ;
    doap:location <https://github.com/usuario/miapp> ] .
```
#### FOAF (Friend of a Friend)
Vocabularioo para describir personas, relaciones e intereses
**Clases y propiedades clave:**
- `foaf:Person`, `foaf:Organization`
- `foaf:name`, `foaf:mbox`, `foaf:homepage`, `foaf:img`
- `foaf:knows`, `foaf:interest`, `foaf:member`
**Ejemplo**
```turtle
@prefix foaf: <http://xmlns.com/foaf/0.1/> .
:ana a foaf:Person ;
  foaf:name "Ana Torres" ;
  foaf:mbox <mailto:ana.torres@example.org> ;
  foaf:homepage <http://anatorres.example.org> ;
  foaf:interest "Web Semántica", "Inteligencia Artificial" ;
  foaf:knows :carlos .
```
#### Dublin Core
Metadatos para describir recursos
**Elementos clave:**
- `dc:title`, `dc:creator`, `dc:subject`, `dc:description`
- `dc:publisher`, `dc:date`, `dc:type`, `dc:format`
- `dc:identifier`, `dc:language`, `dc:rights`
**Ejemplo**
```turtle
@prefix dc: <http://purl.org/dc/terms/> .
:articulo123 a dc:BibliographicResource ;
  dc:title "La Web Semántica en la educación superior"@es ;
  dc:creator "Ana Torres" ;
  dc:subject "Web Semántica, Educación, RDF" ;
  dc:description "Artículo académico que analiza el impacto de la Web Semántica en la docencia universitaria."@es ;
  dc:publisher "Universidad Rey Juan Carlos" ;
  dc:date "2024-05-10"^^xsd:date ;
  dc:type "Artículo científico"@es ;
  dc:format "application/pdf" ;
  dc:identifier <http://ejemplo.org/articulo/123> ;
  dc:language "es" ;
  dc:rights "Licencia CC-BY 4.0"@es .
```
### Aplicaciones de la Web Semántica
#### Anotación de datos no estructurados
- Uso de RDFa para añadir metadatos semánticos en HTML
- Ejemplo: Google Dataset Search indexa páginas anotadas con `schema:Dataset`
#### Integración de datos
- Conversión de datos en varios formatos a RDF mediante herramientas como GRDDL, RDFa, etc.
- Uso de SPARQL y razonadores OWL para consultar y enriquecer datos
#### Web of Things
- Estándar del W3C para integrar dispositivos IoT, véase [[Inteligencia Ambiental y Computación Obicua]] con la Web Semántica
- Describe dispositivos como recursos web con propiedades, acciones y eventos
- **Ejemplo**

```turtle
:SmartBulb123 a wot:Thing ;
  wot:title "Bombilla Inteligente"@es ;
  wot:hasPropertyAffordance :brightness ;
  wot:hasActionAffordance :turnOn, :turnOff .
```
## DBpedia vs Wikidata
Existen bases de datos masivas que ya describen el mundo (ciudades, famosos, peliculas...). Las dos más importantes son estas.
### A. DBpedia: Wikipedia
Primer gran proyecto con limitaciones.
- Funciona con un bot que lee "**infoboxes**" (cuadros de resumen a la derecha de los artículos de Wikipedia) y los traduce automáticamente a RDF.
- El problema es que es un volcado estático. Si wikipedia cambia hoy, DBpedia no se entera hasta que vuelva a pasar el bot. Además, si se escribe mal la infobox, DBpedia tendrá errores.
### B. Wikidata
Base de datos creada para ser leída por máquinas y humanos a la par. Hermana de Wikipedia pero independiente.
- Los usuarios editan los datos directamente en formato estructurado
- Wikidata no usa palabras en inglés o español para definir las cosas, usa **códigos**
	- **Items (Q)** Las cosas (Sujetos). *Ej* `Q220292344` es Star Wars
	- **Properties (P)** Las relaciones (Predicados). *Ej* `P179` es "parte de la serie"
- Como usa códigos, la interfaz lo traduce automáticamente a tu idioma.

|**Característica**|**DBpedia**|**Wikidata**|
|---|---|---|
|**Origen**|Extraído automáticamente de Wikipedia.|Editado manualmente por usuarios (como una wiki).|
|**Actualización**|Lenta (depende de cuándo extraigan los datos).|**Tiempo real** (si cambias un dato, se refleja al instante).|
|**Estructura**|Ontología fija basada en las infoboxes.|Flexible (Declaraciones con referencias).|
|**Idiomas**|Centrado en versiones por idioma (DBpedia en español, en inglés...).|**Nativo Multilingüe** (un solo código Q sirve para todos).|
|**Identificadores**|`dbpedia:Madrid`|`wd:Q2807` (Madrid)|
### Ejemplo práctico: Consulta en WikiData
Si quisiésemos buscar en Wikidata películas de la saga Star Wars, se vería así.

>[!NOTE]
>En wikidata el prefijo para propiedades es `wdt:` y para items es `wd:`

```SPARQL
SELECT ?item ?itemLabel
WHERE {
	# Buscamos items (?item) que tengan la propiedad P179 
	# y cuyo valor sea Q22092344 (Star Wars)
	?item wdt:P179 wd:Q22092344
	
	# Servicio de wikidata
	# devuelve el nombre en texto automáticamente (?itemLabel)
	SERVICE wikibase:label { bd:serviceParam wikibase:language "      [AUTO_LANGUAGE], en". }
}
```