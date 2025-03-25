## État des fonctionnalités du compilateur IFCC

Ce tableau résume le support des fonctionnalités du projet IFCC à date, réparties en niveaux de priorité.

---

### 🟢 Ultra prioritaires --> À finir le 26 MARS 2025 (SPRINT 1)

| Fonctionnalité | État | Détails |
|----------------|------|---------|
| **Type `int` (32 bits)** | ✅ Implémenté | Utilise `movl`, `%eax`, `%rbp` pour 32 bits |
| **Variables** | ✅ Implémenté | Gérées via `SymbolTableVisitor` |
| **Constantes entières et caractères `'a'`** | ⚠️ Partiellement| Constantes (`ConstExpr`), caractères (`CharConstExpr`), mais type char pas encore géré |
| **Opérations `+`, `-`, `*`** | ✅ Implémenté | `visitAddSub`, `visitMulDiv` avec registres temporaires |
| **Division et Modulo** | ✅ Implémenté | `idivl`, `cltd`, `%` via `%edx` |
| **Bitwise `\|`, `&`, `^`** | ✅ Implémenté | `visitBitwiseExpr()` |
| **Comparaisons `==`, `!=`, `<`, `>`, `<=`, `>=`** | ✅ Implémenté | `visitCmpExpr()` avec `set*` |
| **Opérateurs unaires `!`, `-`** | ✅ Implémenté | `NegateExpr`, `NotExpr` |
| **Déclaration de variables n'importe où** | ✅ Implémenté | Géré dans la grammaire |
| **Affectation (= retourne une valeur)** | ⚠️ *Partiellement* | Stockée mais pas encore utilisée comme valeur |
| **Entrées-sorties (`putchar`, `getchar`)** | ❌ Non implémenté | Aucun appel système ou standard |
| **Définition de fonctions avec paramètres** | ❌ Non implémenté | Uniquement `main()` supporté |
| **Vérification des appels de fonctions** | ❌ Non implémenté | Aucune vérification d'arguments |
| **Structure de blocs `{}`** | ✅ Implémenté | Reconnue par la grammaire |
| **Support des portées et shadowing** | ❌ Non implémenté | Table des symboles globale |
| **Structures `if`, `else`, `while`** | ❌ Non implémenté | Pas encore dans la grammaire |
| **`return` n'importe où** | ✅ Implémenté | Vérifié avec `checkHasReturn()` |
| **Vérification : variable utilisée déclarée** | ✅ Implémenté | `visitVarExpr()` avec erreur si inconnue |
| **Vérification : double déclaration** | ✅ Implémenté | Détection dans `visitDeclaration()` |
| **Vérification : variable déclarée non utilisée** | ✅ Implémenté | Message d’avertissement via `checkUnusedVariables()` |

---

### 🟡 Prioritaires --> À FINIR LE 2 AVRIL 2025 (SPRINT 2)

| Fonctionnalité | État | Détails |
|----------------|------|---------|
| **Reciblage (x86, MSP430, ARM)** | ❌ Non implémenté | Cible uniquement x86-64 |
| **`double` et conversions** | ❌ Non implémenté | Aucun support pour types flottants |
| **Propagation de constantes** | ❌ Non implémenté | Pas d’optimisation `1+2 → 3` |
| **Propagation de variables constantes** | ❌ Non implémenté | Pas d’analyse de data-flow |
| **Tableaux (1D)** | ❌ Non implémenté | Pas dans la grammaire |
| **Pointeurs** | ❌ Non implémenté | Pas d'accès mémoire indirect |
| **`break` / `continue`** | ❌ Non implémenté | Aucun support de structures de boucle |
| **Chaînes de caractères (`char[]`)** | ❌ Non implémenté | Pas de gestion des littéraux de chaîne |
| **Initialisation à la déclaration** | ✅ Implémenté | Géré dans `visitDeclaration()` |
| **`switch...case`** | ❌ Non implémenté | Pas de règle correspondante |
| **Opérateurs `\|\|`, `&&` (paresseux)** | ❌ Non implémenté | Pas encore dans la grammaire |
| **Opérateurs `+=`, `-=`, `++`, `--`** | ❌ Non implémenté | Aucun support syntaxique ou sémantique |

---

### 🔵 Moins prioritaires --> À FINIR LE 9 AVRIL 2025 (SPRINT 3)

| Fonctionnalité | État | Détails |
|----------------|------|---------|
| **Variables globales** | ❌ Non implémenté | Uniquement locales |
| **Types `inttypes.h`, `float`** | ❌ Non implémenté | Seul `int` est supporté |
| **Opérateurs `<<`, `>>`, etc.** | ❌ Non implémenté | Pas dans la grammaire |
| **Structures `for`, `do...while`** | ❌ Non implémenté | Aucune gestion de ces structures |

---

### 🌟 Bonus

| Fonctionnalité | État | Détails |
|----------------|------|---------|
| **Fichiers `.h` / `.c` séparés** | ❌ Non implémenté | Compilation mono-fichier |
| **Préprocesseur `#define`, `#include`** | ❌ Non implémenté | Ignoré par la grammaire |
| **Structures et unions** | ❌ Non implémenté | Aucun support |
| **Type `char` (8 bits)** | ⚠️ *Partiellement* | Support des constantes `char`, mais stockées sur 32 bits |


