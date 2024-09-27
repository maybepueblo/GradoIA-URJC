
install.packages("ggplot2")
library(ggplot2)

# Limpiamos el ambiente de trabajo
rm(list = ls(all = TRUE))

# Iniciamos el trabajo
setwd("C:/Users/pablo/OneDrive/Documentos/Universidad/Probabilidad y Estadística/Trabajo Estadística")

# Leemos los datos
data = read.table("datos_grupo_3.txt", header = TRUE, sep="\t", dec=".")

# Explorando nuestros datos

dim(data) # Dimensión de la tabla

str(data) # Tipos de los datos

summary(data) # Resumen de los datos

names(data) # Nombres de nuestras variables

# Analizamos cada variable

# "Tipo" y su tabla
tabla_tipo = table(data$Tipo)
tabla_tipo

# Diagrama de sectores de "Tipo"
colores = c("white", "black")
pie(tabla_tipo, col = colores, main = "Diagrama de Tipo ")

# "Nºvulnerabilidades"
tabla_vulnerabilidad = table(data$No.vulnerabilidades)
tabla_vulnerabilidad

# Tabla de frecuencias relativas
prop.table(tabla_vulnerabilidad)

# Análisis de variables
summary(data$No.vulnerabilidades)

# Boxplot 
boxplot(data$No.vulnerabilidades, col = "white",main="Boxplot Nº vulnerabilidades")

# "Tiempo"
summary(data$Tiempo)

k=14
d = (max(data$Tiempo)-min(data$Tiempo))/k
límites = min(data$Tiempo)+c(0:k)*d
cortes = cut(data$Tiempo, breaks=límites, include.lowest = T)
tabla_tiempo = table(cortes)
tabla_tiempo

# Histograma "Tiempo"
hist(data$Tiempo, breaks = "Sturges", freq = NULL, main = "Histograma de 'Tiempo'",
labels = FALSE)

# Boxplot "Tiempo"
boxplot(data$Tiempo, col = "white", main="Boxplot 'Tiempo'")

# "Coste"
summary(data$Coste)

k = 10
d = (max(data$Coste)-min(data$Coste))/k
límites = min(data$Coste)+c(0:k)*d
cortes = cut(data$Coste, breaks=límites, include.lowest = T)
tabla_coste = table(cortes)
tabla_coste

# Histograma 'Coste'
hist(data$Coste, breaks = "Sturges", freq = NULL, main = "Histograma de 'Coste'",
labels = FALSE)

# Boxplot 'Coste'
boxplot(data$Coste, col = "000000", main="Boxplot de 'Coste'")

data$Tipo <- as.numeric(factor(data$Tipo)) # Conversión = 1: Crítico, 2: No crítico
data$Tipo

plot(data$Tiempo, data$Tipo, main = "Gráfico Bivariante General Tipo - Tiempo", xlab = "Tiempo", ylab =  "Tipo", col = "black")

ggplot(data, aes(Tiempo, factor(Tipo))) +
  geom_point(colour = "blue") +
  geom_smooth(method = "lm", se = FALSE, colour = "black") +
  ggtitle("Recta de Regresión:") +
  xlab("Tiempo") +
  ylab("Tipo")

cov(data$Tiempo, data$No.vulnerabilidades)

cor(data$Tiempo, data$No.vulnerabilidades)

plot(data$Tiempo, data$No.vulnerabilidades, main = "Gráfico Bivariante General Tiempo - No.vulnerabilidades", xlab = "Tiempo", ylab =  "No.vulnerabilidades", col = "black")

ggplot(data, aes(Tiempo, No.vulnerabilidades)) + ggtitle("Recta de Regresión:") +
  xlab("Tiempo") + ylab("No.vulnerabilidades")+ geom_point(colour = "blue") +
  geom_smooth(method = "lm", se = FALSE, colour = "black")



