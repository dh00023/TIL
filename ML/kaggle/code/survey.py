# https://www.inflearn.com/course/%EB%8D%B0%EC%9D%B4%ED%84%B0-%EC%82%AC%EC%9D%B4%EC%96%B8%EC%8A%A4-kaggle

import pandas as pd
import numpy as np
from scipy import stats
import matplotlib.pyplot as plt
import seaborn as sns

# missingno는 NaN 데이터들에 대해 시각화 해준다.
import missingno as msno

# Suppress Deprecation and Incorrect usage warning
import warnings
warnings.filterwarnings('ignore')

question = pd.read_csv('./kaggle-survey-2017/schema.csv')
print(question.shape) # (290, 3)
print(question.head())

print('\n')

# 선다형 객관식 문제 응답
mcr = pd.read_csv('./kaggle-survey-2017/multipleChoiceResponses.csv', encoding='ISO-8859-1', low_memory=False)
print(mcr.shape) # (16716, 228)
print(mcr.columns)
print(mcr.head())

print('\n')

msno.matrix(mcr, figsize=(12,5)) # competition 참여시 NaN 데이터를 시각화하여 보면 도움이 된다.


# 성별 
sns.countplot(y='GenderSelect', data=mcr)
plt.show()

# 국가별 응답수
con_df = pd.DataFrame(mcr['Country'].value_counts())
print(con_df.tail())

con_df['국가'] = con_df.index
con_df.columns = ['응답 수', '국가']

con_df = con_df.reset_index().drop('index',axis=1)

# 연령
mcr['Age'].describe()
sns.distplot(mcr[mcr['Age']>0]['Age']) # 0세 이상 시각화
plt.show()

# 학력
sns.countplot(y='FormalEducation', data=mcr)
plt.show()

# 전공
mcr_major_count = pd.DataFrame(mcr['MajorSelect'].value_counts())
mcr_major_percent = pd.DataFrame(mcr['MajorSelect'].value_counts(normalize=True))
mcr_major_df = mcr_major_count.merge(mcr_major_percent, left_index=True, right_index=True)
print(mcr_major_df)

plt.figure(figsize=(12,16))
sns.countplot(y='MajorSelect', data=mcr)
plt.show()

# 취업여부
mcr_es_count = pd.DataFrame(mcr['EmploymentStatus'].value_counts())
mcr_es_percent = pd.DataFrame(mcr['EmploymentStatus'].value_counts(normalize=True))
mcr_es_df = mcr_es_count.merge(mcr_es_percent, left_index=True, right_index=True)
mcr_es_df.columns = ['응답 수', '비율']
print(mcr_es_df)
sns.countplot(y='EmploymentStatus', data=mcr)


# 프로그래밍 경험
sns.countplot(y='Tenure', data=mcr)

# 우리나라 데이터
korea = mcr.loc[(mcr['Country'] == 'South Korea')]
sns.distplot(korea['Age'].dropna())

figure, (ax1, ax2) = plt.subplots(ncols=2)

figure.set_size_inches(12, 5)
sns.distplot(korea['Age'].loc[korea['GenderSelect']=='Female'].dropna(), norm_hist=False, color=sns.color_palette('Paired')[4], ax=ax1)
ax1.set_title('korean Female')
sns.distplot(korea['Age'].loc[korea['GenderSelect']=='Male'].dropna(), norm_hist=False, color=sns.color_palette('Paired')[0], ax=ax2)
ax2.set_title('korean Male')


sns.barplot(x=korea['EmploymentStatus'].unique(), y=korea['EmploymentStatus'].value_counts(normalize=True))
plt.xticks(rotation=30, ha='right')
plt.title('Employment status of the korean')
plt.ylabel('')


full_time = mcr.loc[(mcr['EmploymentStatus'] == 'Employed full-time')]
looking_for_job = mcr.loc[(mcr['EmploymentStatus'] == 'Not employed, but looking for work')]


# 자주 묻는 질문

# Q1. python과 r중 어떤 언어를 배워야할까요?
sns.countplot(y='LanguageRecommendationSelect', data=mcr)

# 현재 하고 있는 일
sns.countplot(y= mcr['CurrentJobTitleSelect'])
mcr[mcr['CurrentJobTitleSelect'].notnull()]['CurrentJobTitleSelect'].shape
data = mcr[(mcr['CurrentJobTitleSelect'].notnull()) & ((mcr['LanguageRecommendationSelect'] == 'Python') | (mcr['LanguageRecommendationSelect'] == 'R'))]
sns.countplot(y='CurrentJobTitleSelect', hue='LanguageRecommendationSelect', data=data) # hue는 해당 데이터 값에 따라 색상 다르게 출력


# Q2. 데이터 사이언스 분야에서 앞으로 크게 주목받을 것은 무엇일까요?
mcr_ml_tool_count = pd.DataFrame(mcr['MLToolNextYearSelect'].value_counts())
mcr_ml_tool_percent =  pd.DataFrame(mcr['MLToolNextYearSelect'].value_counts(normalize=True))
mcr_ml_tool_df = mcr_ml_tool_count.merge(mcr_ml_tool_percent, left_index=True, right_index=True)
mcr_ml_tool_df.columns = ['응답 수', '비율']

plt.figure(figsize=(9,6))
data = mcr['MLMethodNextYearSelect'].value_counts().head(15)
sns.barplot(y=data.index, x=data)

# Q3. 어디에서 데이터 사이언스를 배워야할까?
mcr['LearningPlatformSelect'] =  mcr['LearningPlatformSelect'].astype('str').apply(lambda x : x.split(','))
s = mcr.apply(lambda x: pd.Series(x['LearningPlatformSelect']), axis=1).stack().reset_index(level=1, drop=True)
s.name = 'platform'
data = s[s != 'nan'].value_counts().head(15)
sns.barplot(y=data.index, x=data)

# 질문 내용보기
qc = question.loc[question['Column'].str.contains('LearningCategory')]
use_features = [ x for x in mcr.columns if x.find('LearningPlatformUsefulness') != -1]

fdf = {}
for feature in use_features:
	a = mcr[feature].value_counts()
	a = a/a.sum()
	fdf[feature[len('LearningPlatformUsefulness'):]] = a

fdf = pd.DataFrame(fdf).transpose().sort_values('Very useful', ascending=False)
sns.heatmap(fdf.sort_values('Very useful', ascending=False), annot=True)


fdf.plot(kind='bar', figsize=(20,8), title="Usefullness of Learning Platforms")
cat_features = [x for x in mcr.columns if x.find('LearningCategory') != -1]

cdf = {}
for feature in cat_features:
	cdf[feature[len('LearningCategory'):]] = mcr[feature].mean()

cdf = pd.Series(cdf)

plt.pie(cdf, labels=cdf.index, autopct='%1.1f%%', shadow=True, startangle=140)
plt.axis('equal')
plt.title("Contribution of each platform to Learning")

# Q4. 데이터 과학을 위해 높은 사양의 컴퓨터가 필요한가?
qc = question.loc[question['Column'].str.contains('HardwarePersonalProjectsSelect')]
print(qc.shape)
mcr[mcr['HardwarePersonalProjectsSelect'].notnull()]['HardwarePersonalProjectsSelect'].shape

mcr['HardwarePersonalProjectsSelect'] = mcr['HardwarePersonalProjectsSelect'].astype('str').apply(lambda x : x.split(','))
s = mcr.apply(lambda x: pd.Series(x['HardwarePersonalProjectsSelect']), axis=1).stack().reset_index(level=1, drop=True)
s.name = 'hardware'

s = s[s!='nan']
pd.DataFrame(s.value_counts())

# Q5. 데이터 사이언스 공부에 얼마나 많은 시간을 사용하는가?
plt.figure(figsize=(6,8))
sns.countplot(y='TimeSpentStudying', data=mcr, hue='EmploymentStatus').legend(loc='best', bbox_to_anchor=(1,0.5))

figure, (ax1, ax2) = plt.subplots(ncols=2)
figure.set_size_inches(12, 5)
sns.countplot(x='TimeSpentStudying', data=full_time, hue='EmploymentStatus', ax=ax1).legend(loc='best', bbox_to_anchor=(1, 0.5))
sns.countplot(x='TimeSpentStudying', data=looking_for_job, hue='EmploymentStatus', ax=ax2).legend(loc='best', bbox_to_anchor=(1, 0.5))


# Q6. 블로그, 팟캐스트, 수업, 기타 등등 추천할만한 것이 있는지
mcr['BlogsPodcastsNewslettersSelect'] = mcr['BlogsPodcastsNewslettersSelect'].astype('str').apply(lambda x: x.split(','))
s = mcr.apply(lambda x: pd.Series(x['BlogsPodcastsNewslettersSelect']), axis=1).stack().reset_index(level=1, drop=True)
s.name = 'platforms'

s = s[s != 'nan'].value_counts().head(20)
plt.figure(figsize=(6,8))
plt.title("Most Popular Blogs and Podcasts")
sns.barplot(y=s.index, x=s)

mcr['CoursePlatformSelect'] = mcr['CoursePlatformSelect'].astype('str').apply(lambda x: x.split(','))
mcr['CoursePlatformSelect'].head()

t = mcr.apply(lambda x: pd.Series(x['CoursePlatformSelect']), axis=1).stack().reset_index(level=1, drop=True)
t.name = 'courses'
t = t[ t != 'nan'].value_counts().head()

sns.barplot(y=t.index,x=t)

# Q7. 데이터 사이언스 직무에서 가장 중요하다고 생각되는 스킬
job_features = [ x for x in mcr.columns if x.find('JobSkillImportance') != -1 and x.find('JobSkillImportanceOther') == -1]

jdf = {}
for feature in job_features:
	a = mcr[feature].value_counts()
	a = a/a.sum()
	jdf[feature[len('JobSkillImportance'):]] = a

jdf = pd.DataFrame(jdf).T

plt.figure(figsize=(10,6))
sns.heatmap(jdf.sort_values("Necessary", ascending=False), annot=True)
jdf.plot(kind='bar', figsize=(12,6), title='Skill Importance in Data Science Jobs')

# Q8. 데이터 과학자의 평균 급여는 얼마나 될까?
mcr[mcr['CompensationAmount'].notnull()].shape

mcr['CompensationAmount'] = mcr['CompensationAmount'].str.replace(',', '')
mcr['CompensationAmount'] = mcr['CompensationAmount'].str.replace('-', '')

rates = pd.read_csv('./kaggle-survey-2017/conversionRates.csv')
rates.drop('Unnamed: 0', axis=1, inplace=True)

salary = mcr[['CompensationAmount', 'CompensationCurrency', 'GenderSelect', 'Country', 'CurrentJobTitleSelect']].dropna()
salary = salary.merge(rates, left_on='CompensationCurrency', right_on='originCounry', how='left')

salary['Salary'] = pd.to_numeric(salary['CompensationAmount']) * salary['exchangeRate']
salary.head()

print('Maximum Salary is USD $',salary['Salary'].dropna().astype(int).max())
print('Minimum Salary is USD $',salary['Salary'].dropna().astype(int).min())
print('Median Salary is USD $',salary['Salary'].dropna().astype(int).median())

plt.subplots(figsize=(15, 8))
salary = salary[salary['Salary'] < 500000]
sns.distplot(salary['Salary'])
plt.axvline(salary['Salary'].median(), linestyle='dashed') # 평균 선
plt.title('Salary Distribution', size=15)

# 국가별 급여
plt.subplots(figsize=(8,12))
sal_coun = salary.groupby('Country')['Salary'].median().sort_values(ascending=False)[:30].to_frame()

sns.barplot('Salary', sal_coun.index, data=sal_coun, palette='RdYlGn')
plt.axvline(salary['Salary'].median(), linestyle='dashed') # 평균 선
plt.title('Highest Salary Paying Countries')

# 한국 급여
salary_korea = salary.loc[(salary['Country'] == 'South Korea')]
plt.subplots(figsize=(8,4))
sns.boxplot(y='GenderSelect', x='Salary', data=salary_korea)

# Q9. 개인 프로젝트나 학습용 데이터를 어디에서 얻을까?
mcr['PublicDatasetsSelect'] = mcr['PublicDatasetsSelect'].astype('str').apply(lambda x: x.split(','))
q = mcr.apply(lambda x: pd.Series(x['PublicDatasetsSelect']),axis=1).stack().reset_index(level=1, drop=True)
q.name='courses'

q = q[q!='nan'].value_counts()
pd.DataFrame(q)

# 데이터 사이언티스트가 되기 위해 학위가 중요할까?
sns.countplot(y='UniversityImportance', data=mcr)

import plotly.offline as py
import plotly.figure_factory as fig_fact

top_uni = mcr['UniversityImportance'].value_counts().head(5)
top_uni_dist = []
for uni in top_uni.index:
	top_uni_dist.append[mcr(mcr['Age'].notnull())&(mcr['UniversityImportance']==uni)]['Age']


group_labels = top_uni.index
fig = fig_fact.create_distplot(top_uni_dist, group_labels, show_hist=False)
py.iplot(fig, filename='University Importance by Age')
plt.show()
