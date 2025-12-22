## Herramientas y aplicaciones
### Frameworks
Bibliotecas y entornos de programación que permiten crear, manipular y consultar grafos RDF y ontologías. Proporcionan APIs para integrar la Web Semántica en aplicaciones reales.

**Importancia**
- Facilitan el desarrollo de aplicaciones semánticas sin implementar todo desde cero
- Son la base técnica para crear herramientas, portales de datos abiertos y sistemas de razonamiento.

**Usos**
- Construcción de grafos RDF
- Ejecución de consultas SPARQL
- Carga y exportación de ontologías en distintos formatos
- Creación de APIs semánticas para integrar datos en aplicaciones

**Ejemplos principales**
- **RDFLib** - Creación de grafos RDF, lectura/escritura en Turtle, RDF/XML, N-Triples, consultas SPARQL
- **Apache Jena** - Motor SPARQL (ARQ), almacenamiento de triples (TDB), razonadores básicos
- **OWL API** - Enfocado en ontologías OWL, usado en edición y razonamiento
- **RDF4J** - Framework modular para RDF, compatible con SPARQL y Linked Data
### Editores de Ontologías
Aplicaciones gráficas que permiten diseñar, visualizar y modificar ontologías de manera intuitiva

**Importancia**
- Sin editores, sería muy complejo escribir manualmente ficheros RDF/OWL
- Permiten a expertos no técnicos colaborar en la construcción de ontologías
- Integran razonadores para verificar consistencia

**Usos**
- Crear ontologías desde cero
- Extender vocabularios existentes
- Documentar y mantener ontologías
- Docencia

**Ejemplo principal**
- **Protégé** (Stanford)
	- Más usado nivel mundial
	- RDF, RDFS y OWL
	- Visualización en grafo, formularios de edición y verificación de consistencia
	- Extensible con plugins
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
## La Web de Datos (Linked Data)
### Principios de Linked Data
1. Usar IRIs para identificar cosas
2. Usar HTTP para acceder a esas IRIs
3. Proporcionar información útil usando estándares
4. Incluir enlaces a otras IRIs
### Fuentes de datos destacadas
- DBpedia - datos estructurados de wikipedia
- Wikidata - base de conocimiento colaborativa y multilingüe
- Datos abiertos - gobierno de españa, ayuntamiento de madrid, etc.
### Ejemplo DBpedia
- SPARQL Endpoint https://dbpedia.org/sparql
- Ejemplo de consulta para obtener porteros de fútbol con condiciones específicas
### Ejemplo Wikidata
- **Elementos clave**
	- **Items (Q)** tienen identificadores únicos
	- **Propiedades (P)** relaciones
- **Consulta SPARQL** ejemplo:
```sparql
SELECT ?item ?itemLabel
WHERE {
  ?item wdt:P179 wd:Q22092344.  # Part of the series "Star Wars"
  SERVICE wikibase:label { bd:serviceParam wikibase:language "[AUTO_LANGUAGE]". }
}
```
### Comparativa DBpedia vs Wikidata

| Aspecto        | DBpedia                      | Wikidata                                |
| -------------- | ---------------------------- | --------------------------------------- |
| Origen         | Extraído de wikipedia (2007) | Proyecto de wikimedia (2012)            |
| Fuente         | Infoboxes de wikipedia       | Contribuciones directas                 |
| Modelo         | RDF con odontología fija     | Declaraciones flexibles con referencias |
| Multilingüismo | Limitado                     | Multilingüe por diseño                  |
| Actualización  | Automática, menos frecuente  | Manual y en tiempo real                 |

