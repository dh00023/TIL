# 관계데이터 모델

관계데이터 모델은 동일한 구조의 관점에서 모든 데이터를 논리적으로 구성, 선언적인 질의어를 통한 데이터 접근을 제공한다. 관계데이터 모델의 목적은 높은 **데이터 독립성**을 제공하는 것이다.

## 2.1 기본적인 용어

![](http://cfile22.uf.tistory.com/original/17385D474D71A69C269849)
* 릴레이션 : 2차원 테이블로 고유한 이름을 가진다.
* 튜플(=레코드) : 릴레이션의 각 헹으로 릴레이션이 나타내는 엔티티의 특정 인스턴스에 관한 값들이다.
* 애트리뷰트 : 릴레이션에서 이름을 가진 하나의 열
* 도메인 : 한 애트리뷰트에 나타날 수 있는 값들의 집합이다. 동일한 도메인이 여러 애트리뷰트에서 사용될 수 있다.
* 차수(degree) : 한 릴레이션에 들어 있는 애트리뷰트들의 수. 유효한 릴레이션의 최소 차수는 1.
* 카디날리티 : 릴레이션의 튜플 수. 유효한 릴레이션의 최소 카디날리티 수는 0.
* Null 값 : '알려지지 않음' 또는 '적용할 수 없음'
* 릴레이션 스키마 : 릴레이션의 이름과 애트리뷰트들의 집합, 내포(intension)
> 릴레이션이름(++애트리뷰트1++, 애트리뷰트2, ...,애트리뷰트N)
* 릴레이션 인스턴스 : 릴레이션의 한 시점에 있는 투플들의 집합이다. 시간의 흐름에 따라 계속 변한다. 외연(extension)

## 2.2 릴레이션 특성
1. 각 릴레이션은 오직 하나의 레코드 타입만 포함한다.
2. 한 애트리뷰트 내의 값들은 모두 같은 유형이다.
3. 애트리뷰트들의 순서는 중요하지 않다.
4. 동일한 튜플이 두 개 이상 존재하지 않는다.
5. 한 튜플의 각 애트리뷰트는 원자값을 갖는다.(값들의 리스트나 집합은 허용되지 않음)
6. 튜플의 순서는 중요하지 않다.
7. 각 애트리뷰트의 이름은 한 릴레이션 내에서 만 고유하다.

## 2.3 릴레이션 키
: 각 튜플을 고유하게 식별할 수 있는 하나 이상의 애트리뷰트들의 모임.

일반적으로 키는 두 릴레이션을 서로 연관시키는데 사용된다. 따라서 여러 릴레이션에 불필요한 중복을 피하기위해 가능하면 키를 구성하는 애트리뷰트값이 적으면 좋다.

### 1. 수퍼키(superKey)
한 릴레이션 내의 특정 투플을 고유하게 식별하는 하나의 애트리뷰트 또는 애트리뷰트의 집합.
수퍼키의 문제점은 투플들을 고유하게 식별하는데 꼭 필요하지 않은 애트리뷰트들을 포함할 수 있다.

### 2. 후보키(candidate key)
각 투플을 고유하게 식별하는 최소한의 애트리뷰트들의 모임. 즉, 후보키를 구성하는 애트리뷰트들 중 어느 하나라도 빠지면 고유하게 식별하는 능력이 사라진다. 모든 릴레이션에는 최소한 한개의 후보키가 있다. 후보키도 두 개 이상의 애트리뷰트로 이루어 질 수 있으며 이러한 경우 **복합키(composite key)**라고 부른다.

### 3. 기본키(primary key)
한 릴레이션에 후보키가 두개 이상 있으면 데이터베이스 설계자 or 관리자가 이들 중 하나를 기본키로 선정한다.
자연스러운 기본 키를 찾을 수 없는 경우에 종종 인위적인 키 애트리뷰트를 추가할 수 있는데 이러한 키를 **대리키(surrogate key)**라고 한다.

* 고려할 사항
	* 애트리뷰트가 항상 고유한 값을 가질 것인가
	* 애트리뷰트가 확실하게 널값을 갖지 않을 것인가
	* 애트리뷰트 값이 변경될 가능성이 높은 애트리뷰트는 기본키로 선정하지 말 것
	* 가능하면 작은 정수 값으나 짧은 문자열
	* 가능하면 복합 기본키는 피할 것

### 4. 대체키(alternate key)
기본키로 선정되지 않은 후보키.

### 5. 외래키(foreign key)
어떤 릴레이션의 기본키를 참조하는 애트리뷰트로 관계 데이터베이스에서 릴레이션들 간의 관계를 나타내기 위해서 사용된다. 외래키 애트리뷰트는 참조되는 릴레이션의 기본키와 동일한 도메인을 가져야한다. 외래키는 자신이 속한 릴레이션의 기본 키의 구성요소가 되거나 되지 않을 수 있다.

![](http://cfile21.uf.tistory.com/image/217E1E3655136CC434CC40)

## 2.4 무결성 제약조건
**데이터 무결성(data integrity)** 데이터의 정확성 또는 유효성을 의미한다. 무결성 제약조건의 목적은 일관된 데이터베이스 상태를 정의하는 규칙들을 묵시적 또는 명시적으로 정의하는 것이다.
* 특징
	* 스키마의 한 부분
	* 데이터베이스의 상태에 대한 제한
	* DBMS가 시행
	* 릴레이션 내의 무결성 제약조건 : 오직 한 릴레이션만 포함. 릴레이션 스키마의 한 부분
	* 릴레이션 간의 무결성 제약조건 : 여러 릴레이션을 포함. 릴레이션 스키마 또는 데이터베이스 스키마의 한 부분.

### 1. 도메인 제약조건
각 애트리뷰트 값이 반드시 원자값이어야하며, 데이터 형식을 통해 값들의 유형을 제한한다. 또한 애트리뷰트의 default값을 지정하고, 저장되는 값들의 범위를 제한 할 수 있다. 도메인 제약 조건은 어느 정도의 데이터 무결성을 유지한다.

### 2. 키 제약조건
키 애트리뷰트에 중복된 값이 존재해서는 안된다는 것이다.
> 기본키로 정의(null값 허용X)하거나 UNIQUE(null값 허용)명시한 애트리뷰트에는 중복된 값이 허용되지 않음.

### 3. 기본 키와 엔티티 무결성 제약조건
릴레이션의 기본키를 구성하는 어떤 애트리뷰트도 널값을 가질 수 없다.(대체 키에는 적용되지 않음)

### 4. 외래키와 참조 무결성 제약조건
두 릴레이션의 연관된 튜플들 사이의 일관성을 유지하는데 사용. 릴레이션 사이의 관계들이 다른 릴레이션의 기본키를 참조하는 것을 기반으로하여 묵시적으로 표현되기 때문에 외래키 개념이 중요.
> 외래키의 값은 참조되는 릴레이션의 기본키의 값과 같거나, 기본키를 구성하지않으면 널값을 가진다.

### 5. 무결성 제약조건의 유지
데이터베이스에 대한 갱신연산(삽입, 삭제, 수정 연산)의 수행결과에 따라서 제약 조건이 위배 될 수 있다. DBMS는 외래키가 갱신되거나, 참조된 키가 갱신되었을때 참조 무결성 제약조건이 위배되지 않도록 해야한다.

#### 삽입
참조되는 릴레이션에 새로운 튜플이 삽입되면 참조 무결성 제약조건은 위배되지 않는다. 그러나 새로 삽입되는 튜플의 기본키 애트리뷰트의 값에 따라서는 도메인 제약조건, 키 제약조건, 엔티티 무결성 제약조건을 위배할 수 있다. 또한 참조하는 릴레이션에 새로운 튜플을 삽입할 때 도메인, 키 , 엔티티 무결성, 참조 무결성 제약조건이 위배될 수 있다.

#### 삭제
참조하는 릴레이션에서 튜플이 삭제되면 도메인, 키, 엔티티 무결성, 참조 무결성 제약조건등 모든 제약조건을 위배하지 않는다. 그러나 참조되는 릴레이션에서 투플이 삭제되면 참조 무결정 제약조건을 위배하는 경우가 생기거나 생기지 않을 수 있다.
1. 제한(restiricted)
위배를 야기한 연산을 단순히 거절
2. 연쇄(cascade)
참조되는 릴레이션에서 투플을 삭제하고, 참조하는 릴레이션에서 투플을 참조하는 튜플들도 함께 삭제.
3. 널값(nullify)
참조되는 릴레이션에서 투플을 삭제하고, 참조하는 릴레이션에서 투플을 참조하는 투플들의 외래키에 널값을 넣는다.
4. 디폴트값
널값을 넣는 대신에 디폴트 값을 넣는다.

#### 수정
수정연산에 대해 무결성 제약조건을 유지하기위해서 수정하는 애트리뷰트가 기본 키인지 외래 키인지 검사한다. 수정하려는 애트리뷰트가 기본키도 아니고 외래키도 아니면 수정연산이 참조 무결성 제약조건을 위배하지 않는다.
기본 키나 외래키를 수정하는 것은 위의 삽입, 삭제 규칙이 적용된다.

위의 규칙들을 지키지 않을 시에는 거절된다.

