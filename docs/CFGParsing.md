# CFG: Parsing

### Terminology

* **Whitespace: (` `)** Any spacing character that separates tokens.
* **Comment: (`;`)** Text ignored by parser, lasts until end of line. (Treated as **Whitespace**)
* **Token:** Any group of **non-Whitespace/Comment** characters.
* **Property:** Information assigned to a name, consists of a **Key** and **Value**.
* **Key:** The name identifier of a **Property** or **Block**.
* **Value:** The text information associated with a **Property's** **Key**.
* **Block:** A special **Property** that contains other **Properties**. Usually described as the actual contents of said special **Property**.
* **Child:** Any **Property** or **Block** contained within another **Block**.
* **Parent:** The **Block** containing a child **Property** or **Block**.
* **Open Brace: (`{`)** Beginning of a **Block**. (**Block** property's children)
* **Close Brace: (`}`)** End of a **Block**. (**Block** property's children)
* **Namespace:** Another term to describe a **Block**, usually when discussing separation of information.
* **Depth:** The number of **Blocks** deep a **Property** is.
* **Root:** A **Property** or **Block** that is not contained within another **Block**. (**Depth** equals `0`)

<!--

* **Whitespace:** Any spacing character that separates tokens.
* **Comment:** Text ignored by parser, lasts until end of line. (Treated as **Whitespace**)
* **Token:** Any group of **non-Whitespace/Comment** characters.
* **Property:** Information assigned to a name, consists of a **Key** and **Value**.
* **Key:** The name identifier of a **Property** or **Block**.
* **Value:** The text information associated with a **Property's** **Key**.
* **Block:** A special **Property** that contains child **Properties**.
* **Child:** Any **Property** or **Block** contained within another **Block**.
* **Parent:** The **Block** containing a child **Property** or **Block**.
* **Open Brace:** Beginning of a **Block's** children.
* **Close Brace:** End of a **Block's** children.
* **Namespace:** Another term to describe a **Block**, usually when discussing separation of information.

-->

### Character Types

Rows are listed in the order that parsing occurs. First, all whitespace and comments are normalized, then tokens are parsed.

|Category|Characters|Notes|
|:-|:-|:-|
|Comment|`;`|**Whitespace** until **Newline**|
|Newline|`\n` &sup1;|End of `;` **Comments**|
|Whitespace|&zwj;`' '`, `\t`, `\n`, `\r` &sup1;|Required to separate tokens|
|Token|*any other char*|Including `{` and `}` characters|
|Open Brace|`{` &sup2;|Match **exactly**. Only if **Value** token of property|
|Close Brace|`}` &sup2;|Match **exactly**|

\[1\]: The characters listed are <kbd>Space</kbd>, <kbd>Tab&#x21C6;</kbd>, <kbd>Enter&#x21B2;</kbd>, and a second character created by <kbd>Enter&#x21B2;</kbd>.

\[2\]: Open and Close Braces can only be matched **exactly**, the full token must consist of only this one character.

### Token Types

Rows are listed in the order that parsing occurs.

|Token      |Notes   |
|:----------|:-------|
|Close Brace|Matched at any time, does not affect **Key**/**Value** parser state<br>**Depth - 1**|
|Key        |First matched token (that is not `}`)|
|Value      |Second matched token (that is not `}`)<br>**Start new property**|
|Open Brace |**Value** token equals `{`<br>**Depth + 1**|

<!--
|Open Brace |Value token equals `{` (treated as **Value**)<br>**Depth + 1**|
* Key
* Value
* Open Brace
* Close Brace
* Key -> Value (check if Open Brace)
* Close Brace

|Token|Notes|
|:----|:----|
|Close Brace|Can be matched at any time, regardless of key/value parser state<br>Decrement **Depth**|
|Key  |First matched token (and not `}`)|
|Value|Second matched token (and not `}`)|
|Open Brace|Second matched token and `{` (treated as **Value**)<br>Increment **Depth**|
|Whitespace|<kbd>space</kbd> <kbd>\\t</kbd> <kbd>\\n</kbd> <kbd>\\r</kbd>|
|Comment|<kbd>;</kbd>|Whitespace until Newline|
* Key
    * Value
    * Open Brace


\[2\]: Open Braces can **only be matched** when parsing the Value token of a property, when the Key token has already been consumed.

\[3\]: Close Braces can be matched **at any time**. This includes in-bewteen a property key/value pair

### Tokenization

A valid Key or Value token must consist of 1 or more whitespace characters and must not match `}` exactly.

|Category|Characters|
|:-|:-|
|Whitespace|` `, `\t`, `\n`, `\r`|
|Newline|`\n`|
|Comment|`;`|
|Token|*__any__ other character*|
|Open Brace|`{` *only if second token of property!*|
|Close Brace|`}` *can appear anywhere, even in-between property key/values*| 

Whitespace characters: ` `, `\t`, `\n`, `\r`

Newline characters: `\n`

Comment characters: `;`
-->