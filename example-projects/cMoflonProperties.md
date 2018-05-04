## Options
For each algorithm there are a variety of options that you can set in the cMoflon.properties file of your project. This file provides information on all of those and gives some examples
### Syntax
`tc.<Name of the algorithm>.<option> = [CSV]`

`<option> = {parameters,constants,helperclasses,enableHopcountProcess,generateDuplicates,dropUnidirectionalEdges,useEvaluationStatements}`
### The parameters option
Here you should provide the values for the fields that your algorithm specifies. The CSV should be a CSV of key value (Key=Value,...,) pairs, where the key is the name of the specified field,
and the value is either a concrete value (e.g. k=1.5) or a constant (indicated by a const- prefix) defined in the constants property of the algorithm (e.g. k=const-k)
(e.g. KtcAlgorithm specifies a field k hence the property should be `tc.KtcAlgorithm.parameters = k=1.2` or `tc.KtcAlgorithm.parameters = k=const-k`

### The constants option
Here you should specify which constants need to be defined for your algorithm and provide the values for those. The CSV should consist of Key Value Pairs of the form const-<name>=<Value>
(e.g. `tc.KtcAlgorithm.constants=const-k=1.2`

### The helperclasses option
Here you should provide the names of all helperclasses for your TC algorithm in the metamodel (except Node,Link and TCAlgorithm)
(e.g. `tc.LmstAlgorithm.helperclasses = Tree, TreeEntry`)

### The enableHopcountProcess option (off by default)
If your algorithm makes use of hopcounts you should enable it for your algorithm
(e.g `tc.LStarKtcAlgorithm.enableHopcountProcess = true` )

### The generateDuplicates option (off by default)
if you need to traverse links between nodes in both directions you should enable this option (WARNING: uses more memory, can lead to failing executions in large neighborhoods, reduce transmission range to protect against this)
(e.g. `tc.LmstAlgorithm.generateDuplicates = true`)

### The dropUnidirectionalEdges option (on by default)
If you want the framework to keep unidirectional edges you should deactivate this option
(e.g. `tc.LmstAlgorithm.dropUnidirectionalEdges = false`

### The useEvaluationStatements option (off by default)
If you want to obtain information regarding the node degree and runtime for your algorithm you should activate this option
(e.g. `tc.LmstAlgorithm.useEvaluationStatements= true` )
