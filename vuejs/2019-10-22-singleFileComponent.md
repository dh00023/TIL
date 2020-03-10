# Single File Components

Single File Components 체계는 `.vue` 파일로 프로젝트 구조를 구성하는 방식을 말한다. 확장자 `.vue` 파일 1개는 뷰 애플리케이션을 구성하는 1개의 컴포넌트와 동일하다.

```vue
<!--  화면에 표시할 요소들을 정의하는 영역 -->
<template>
<!-- HTML 태그 내용 -->
</template>
```

```vue
<!-- 뷰 컴포넌트의 내용을 정의하는 영역 -->
<script>
exports default{
  // 자바 스크립트 내용
}
</script>
```

```vue
<!-- template에 추가한 HTML 태그의 CSS 스타일을 정의하는 영역 -->
<style>
  /* CSS 스타일 내용 */
</style>
```

## Vue CLI

Single File Component 체계를 사용하기 위해서는 `.vue` 파일을 웹 브라우저가 인식할 수 있는 형태의 파일로 변환해주는 [웹팩(webpack)](https://dh00023.gitbooks.io/javascript/content/posts/2019-10-02-webpack.html)이나 Browserify와 같은 도구가 필요하다. 웹팩은 웹 앱의 자원(HTML, CSS, 이미지)들을 자바스크립트 모듈로 변환해 하나로 묶어 웹 성능을 향상시켜 주는 자바스크립트 모듈 번들러이다. 뷰 개발자들이 편하게 프로젝트를 구성할 수 있도록 CLI(Command Line Interface) 도구를 제공한다.

### 시작하기

```bash
$ vue create <project_name>
```

```bash
Vue CLI v3.11.0
┌───────────────────────────┐
│  Update available: 4.0.4  │
└───────────────────────────┘
? Please pick a preset: (Use arrow keys)
❯ default (babel, eslint)
  Manually select features
```

여기서 default를 선택하여 생성하게 되면 `babel`과 `eslint`가 설치된다. Manually select features를 선택하게 되면 아래와 같이 `vuex`, `vue-router` 등 몇가지를 더 선택할 수 있다.

```
? Please pick a preset: Manually select features
? Check the features needed for your project: (Press <space> to select, <a> to t
oggle all, <i> to invert selection)
❯◉ Babel
 ◯ TypeScript
 ◯ Progressive Web App (PWA) Support
 ◯ Router
 ◯ Vuex
 ◯ CSS Pre-processors
 ◉ Linter / Formatter
 ◯ Unit Testing
 ◯ E2E Testing
```

프로젝트를 하다가 추가적으로 plugin을 설치하고 싶은 경우에는 `add`를 통해 할 수 있다.

default 모드를 선택해 설치하게되면 다음과 같은 구조로 프로젝트가 생성된다.

```
.node_modules/
public/
		favicon.ico
		index.html
src/
    assets/
        logo.png
    components/
        HelloWorld.vue
    App.vue
    main.js
.gitignore
babel.config.js
package-lock.json
package.json
README.md
```

컴포넌트 같은 경우에는 `src/components` 폴더에서 관리한다. 애플리케이션 규모가 커져서 기능별로 관리를 해야하는 경우에는 `components/기능/<컴포넌트명>.vue` (`components/login/LoginForm.vue`)와 같은 형식으로 관리하는 것이 좋다.

```bash
$ vue add <plugin>
```

예를 들어서 `axios` 플러그인을 설치해볼것이다.

```bash
$ vue add axios
📦  Installing vue-cli-plugin-axios...

+ vue-cli-plugin-axios@0.0.4
added 1 package from 1 contributor in 4.648s
✔  Successfully installed plugin: vue-cli-plugin-axios


🚀  Invoking generator for vue-cli-plugin-axios...
📦  Installing additional dependencies...

added 5 packages from 8 contributors in 5.059s
⚓  Running completion hooks...

✔  Successfully invoked generator for plugin: vue-cli-plugin-axios
   The following files have been updated / added:

     src/plugins/axios.js
     package-lock.json
     package.json
     src/main.js

   You should review these changes with git diff and commit them.
```

axios 플러그인이 설치되고 난 후 수정된 파일과 새로 추가된 파일을 확인할 수 있다.

#### 웹팩 설정 파일

`vue-cli 3.x` 에서는 웹팩 설정파일을 노출하지 않는다. 3.x에서는 설정을 추가하기 위해서는 root 디렉토리에 `vue.config.js` 파일을 설정하고 내용을 작성해준다.

```js
// vue.config.js
module.exports = {
  // 여기에 옵션을 작성해준다.
}
```

### vue ui

Vue-CLI3 UI를 통해서 프로젝트를 관리할 수 있다.

```bash
$ vue ui
```

위와 같이 실행하면 프로젝트 매니저가 `localhost:8000`으로 브라우저를 실행시킨다. 이 프로젝트 매니저 위에 프로젝트를 생성할 수 있으며, 이미 생성된 프로젝트를 불러와서 관리 포인트로 둘 수 있다.

### 프로젝트 실행

```bash
$ npm run serve
```

#### build

상용 배포를 위한 빌드를 진행할 수 있다.

```bash
$ npm run build
```

빌드를 실행하면 Vue CLI가 웹팩을 통해 프로젝트의 모든 소스 파일들을 번들링하여 dist 디렉토리에 넣어준다. `dist` 디렉토리를 확인해보면 웹팩이 번들링한 파일들을 확인할 수 있다. 이 파일들은 상용 배포에 적합하도록 웹팩이 최적화 해놓은 것이다.

## 참조

- [Vue CLI](https://cli.vuejs.org/)
- [[Vue.JS] Vue-CLI 3 시작하기](https://kdydesign.github.io/2019/04/22/vue-cli3-tutorial/)