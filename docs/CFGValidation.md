# CFG File Validation


## Regex Patterns

Regular expressions to find and/or replace malformed CFG properties (as lines).

***

### Basics

#### **MATCH:** Token character / Full token
```regexp
[^ \t\r\n;]
[^ \t\r\n;]+
```

#### **MATCH:** Comment character / Full comment
```regexp
;
;.*$
```

#### **MATCH:** Line whitespace / All whitespace
```regexp
[ \t]
[ \t\r\n]
```

***


### Patterns

**Note:** Two pattern choices are included for most sections below. The bottom pattern is available for Regex engines that **do not** support look-ahead or look-behind functionality.


#### **FIND:** Empty lines *(including comments)*
```regexp
^(?=[ \t]*(?:;[^\r\n]*)?$)

^[ \t]*(?:;[^\r\n]*)?$
```


#### **FIND:** Invalid block braces *(not properly spaced)*
```regexp
(?<=[^ \t\r\n;])[{}]|[{}](?=[^ \t\r\n;])

(?:[^ \t\r\n;])[{}]|[{}](?:[^ \t\r\n;])
```


#### **FIND:** Invalid `//` comments
```regexp
(?<!;.*|[^ \t\r\n;])\/\/.*

^([^\r\n;]*[ \t])\/\/.*
```

#### **REPLACE:** Convert invalid `//` comments to `;` comments
```regexp
 Search: (?<!;.*|[^ \t\r\n;])\/\/
Replace: ;

 Search: ^([^\r\n;]*[ \t])\/\/
Replace: $1;
```


#### **FIND:** Lines with 3+ tokens
```regexp
(?<=^[ \t]*)[^ \t\r\n;]+([ \t]+[^ \t\r\n;]+){2,}

^((?:^|[ \t]+)[^ \t\r\n;]+){3,}
```


#### **FIND:** Lines with 3+ tokens *(excluding `//`)*
```regexp
(?<=^[ \t]*)(?!\/\/)[^ \t\r\n;]+([ \t]+(?!\/\/)[^ \t\r\n;]+){2,}

^((?:^|[ \t]+)(?:[^/ \t\r\n;]|/(?:[^/ \t\r\n;]|$))+){3,}
```


#### **REPLACE:** Comment out 3rd line tokens *(strip `//` if present)*
```regexp
(?<=^[ \t]*(?:[^ \t\r\n;]+[ \t]+){2})(?=[^ \t\r\n;])(?:\/\/)?
;

^((?:(?:^|[ \t]+)[^ \t\r\n;]+){2}[ \t]+)(?:\/\/(.)|([^ \t\r\n;]))
$1;$2$3
```


<!-- 
#### This will search for any lines that define 3 or more tokens
```regexp
^[ \t]*[^ \t\r\n;]+[ \t]+[^ \t\r\n;]+([ \t]+[^ \t\r\n;]+)+(?:[ \t;]|$)

^[ \t]*[^ \t\r\n;]+((?:^|[ \t])+[^ \t\r\n;]+){2,}(?:[ \t;]|$)

^((?:^|[ \t]+)[^ \t\r\n;]+){3,}(?=[ \t;]|$)

COMMENT: ^(?=[ \t]*(?:;[^\r\n]*)?$)

(?=;[^\r\n]*$)


^((?:^|[ \t]+)[^ \t\r\n;]+){3,}(?=[ \t;]+|$)
```

To exclude `// ROCK FOG` comment pairs (there's a lot)
```regexp
^[ \t]*[^ \t\r\n;]+[ \t]+[^ \t\r\n;]+([ \t]+(?!// ROCK)[^ \t\r\n;]+)+(?:[ \t;]|$)


^[ \t]*[^ \t\r\n;]+[ \t]+[^ \t\r\n;]+([ \t]+(?!// ROCK)[^ \t\r\n;]+)+(?:[ \t;]|$)
```

#### To exclude all faulty `//` comments
```regexp
^[ \t]*[^ \t\r\n;]+[ \t]+[^ \t\r\n;]+([ \t]+(?!//)[^ \t\r\n;]+)+(?:[ \t;]|$)
```

#### To show **only** faulty `//` comments
```regexp
^[ \t]*[^ \t\r\n;]+[ \t]+[^ \t\r\n;]+([ \t]+(?=//)[^ \t\r\n;]+)+(?:[ \t;]|$)


^[ \t]*(?=//)[^ \t\r\n;]+([ \t]+(?=//)[^ \t\r\n;]+)+(?:[ \t;]|$)
```

#### To show **only** faulty `//` comments that aren't `// ROCK FOG`
```regexp
^[ \t]*[^ \t\r\n;]+[ \t]+[^ \t\r\n;]+([ \t]+(?=//)[^ \t\r\n;]+)+(?:[ \t;]|$)
``` -->