# ft_linear_regression

Projet école 42. Ce projet est une **introduction au machine learning** et a pour but de prédire le **prix d'une voiture** à partir de son **kilométrage**, en utilisant une **fonction linéaire entraînée avec la méthode du gradient descendant**.

---

## Régression linéaire (Linear Regression)

Une **régression linéaire** est une méthode mathématique qui permet de prédire une valeur à partir d'une autre variable en traçant une **ligne droite** qui représente au mieux les données.

Dans ce projet, on effectue une **régression linéaire simple** à une seule caractéristique : le **kilométrage de la voiture**.

La droite cherchée est de la forme :  

```math
Y = aX + b
```

- **X** : variable d’entrée (ce qu’on connaît)  
- **Y** : variable à prédire  
- **a** : pente (influence de X sur Y)  
- **b** : intercept (valeur de Y quand X = 0)  

---

## Algorithme de Gradient Descendant (Gradient Descent Algorithm)

Le **gradient descent** est une méthode permettant de **trouver les meilleurs paramètres d’un modèle** en réduisant progressivement l’erreur.

- Il avance pas à pas dans la direction qui **diminue le plus rapidement l’erreur**  
- Ici, on cherche à déterminer les valeurs de **a** et **b** dans l’équation \(Y = aX + b\)  
- On initialise \(a = 0\) et \(b = 0\), puis on met à jour ces valeurs itérativement

Formules pour la mise à jour :  

```math
b -= learningRate * \frac{\sum(\text{estimatePrice}(mileage[i]) - price[i])}{m}
```

```math
a -= learningRate * \frac{\sum((\text{estimatePrice}(mileage[i]) - price[i]) * mileage[i])}{m}
```

Pour savoir **quand s’arrêter**, on calcule la **fonction de coût**, qui mesure l’erreur du modèle.  
Lorsque sa valeur est suffisamment basse, on sauvegarde **a** et **b**.

⚠️ Il est important de **ne pas trop entraîner le modèle** pour éviter l’**overfitting**.

---

## Overfitting

L’**overfitting** se produit lorsqu’un modèle **apprend trop bien les données d’entraînement**, capturant le bruit et les détails inutiles plutôt que la tendance générale.

**Résultat :**  
- Le modèle fonctionne très bien sur les données d’entraînement  
- Mais il échoue sur de nouvelles données (mauvaise généralisation)

---

## Metrics

Pour évaluer la **performance** de notre modèle, plusieurs métriques peuvent être utilisées.

### MSE (Mean Squared Error)
C’est la moyenne des carrés des erreurs.  
- **Sensibilité aux grandes erreurs** : élevée  
- **À utiliser** : lorsque les grandes erreurs doivent être pénalisées  
- **Unité** : carrée de la variable (ex : km², euro²)  

```math
\text{MSE} = \frac{\sum((\text{RealValue}[i] - \text{PredictedValue}[i])^2)}{n}
```

### RMSE (Root Mean Squared Error)
Même principe que MSE, mais exprimé dans la **même unité que la variable étudiée**.

```math
\text{RMSE} = \sqrt{\frac{\sum((\text{RealValue}[i] - \text{PredictedValue}[i])^2)}{n}}
```

### MAE (Mean Absolute Error)
Erreur absolue moyenne. Chaque erreur a le même poids, donc **moins sensible aux valeurs extrêmes**.

```math
\text{MAE} = \frac{\sum |\text{RealValue}[i] - \text{PredictedValue}[i]|}{n}
```

- Utile si l’on ne veut pas que des événements exceptionnels faussent la métrique globale  
- Exemple : prédiction du trafic web quotidien

### R² (Coefficient de détermination)
Mesure la **proportion de variance expliquée** par le modèle.  
- Varie entre \(-\infty\) et 1 :  
  - 1 → modèle parfait  
  - 0 → prédit aussi mal que la moyenne  
  - <0 → pire que la moyenne

```math
R^2 = 1 - \frac{\sum((\text{RealValue}[i] - \text{PredictedValue}[i])^2)}{\sum((\text{RealValue}[i] - \text{MeanValue})^2)}
```

**Exemple :**  
- Moyenne du poids : 70 kg  
- Si le modèle prédit exactement le poids de chaque personne → R² = 1  
- Si le modèle prédit toujours 70 kg → R² = 0  
- Si le modèle prédit complètement à côté → R² < 0

---

# English Version

# ft_linear_regression

42 School project. This project is an **introduction to machine learning** and aims to **predict the price of a car** based on its **mileage**, using a **linear function trained with the gradient descent method**.

---

## Linear Regression

A **linear regression** is a mathematical method to predict a value from another variable by fitting a **straight line** that best represents the data.

In this project, we perform a **simple linear regression** with a single feature: the **car's mileage**.

The line is of the form:

```math
Y = aX + b
```

- **X**: input variable (known)  
- **Y**: target variable (to predict)  
- **a**: slope (influence of X on Y)  
- **b**: intercept (value of Y when X = 0)  

---

## Gradient Descent Algorithm

Gradient descent is a method that **finds the best model parameters** by gradually reducing the error.

- It moves step by step in the direction that **decreases the error fastest**  
- Here, we want to determine **a** and **b** in the equation \(Y = aX + b\)  
- Initialize \(a = 0\) and \(b = 0\), then update iteratively

Update formulas:

```math
b -= learningRate * \frac{\sum(\text{estimatePrice}(mileage[i]) - price[i])}{m}
```

```math
a -= learningRate * \frac{\sum((\text{estimatePrice}(mileage[i]) - price[i]) * mileage[i])}{m}
```

To know **when to stop**, compute the **cost function**, which measures the model error.  
When low enough, save **a** and **b**.

⚠️ Avoid overtraining to prevent **overfitting**.

---

## Overfitting

**Overfitting** occurs when a model **learns the training data too well**, capturing noise instead of the general trend.

**Result:**  
- Performs well on training data  
- Fails on new data (poor generalization)

---

## Metrics

To evaluate **model performance**, several metrics can be used.

### MSE (Mean Squared Error)
Average of squared errors.  
- **Sensitive to large errors**  
- **Use when** large errors should be penalized  
- **Unit**: squared (e.g., km², euro²)

```math
\text{MSE} = \frac{\sum((\text{RealValue}[i] - \text{PredictedValue}[i])^2)}{n}
```

### RMSE (Root Mean Squared Error)
Same as MSE but in the **same unit as the target variable**.

```math
\text{RMSE} = \sqrt{\frac{\sum((\text{RealValue}[i] - \text{PredictedValue}[i])^2)}{n}}
```

### MAE (Mean Absolute Error)
Average absolute error. Every error has the same weight, **less sensitive to outliers**.

```math
\text{MAE} = \frac{\sum |\text{RealValue}[i] - \text{PredictedValue}[i]|}{n}
```

- Useful when exceptional events should not skew the metric  
- Example: predicting daily website traffic

### R² (Coefficient of Determination)
Measures the **proportion of variance explained** by the model.  
- Range: \(-\infty\) to 1  
  - 1 → perfect model  
  - 0 → predicts as badly as the mean  
  - <0 → worse than the mean

```math
R^2 = 1 - \frac{\sum((\text{RealValue}[i] - \text{PredictedValue}[i])^2)}{\sum((\text{RealValue}[i] - \text{MeanValue})^2)}
```

**Example:**  
- Average weight: 70 kg  
- Predicts exact weight → R² = 1  
- Always predicts 70 kg → R² = 0  
- Completely wrong prediction → R² < 0

