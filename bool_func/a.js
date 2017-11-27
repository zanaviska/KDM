'use strict';

const request = require('request');
const metasync = require('metasync');

const name = 'іп-73';
let lecture2 = 'Шемсединов Т. Г.';
const lecture1 = 'Овчаренко О. В.';
let obj = {
  id: 0,
  teacher_id_1: 0,
  teacher_id_2: 0
}

const fn1 = (data, callback) => request('https://api.rozklad.hub.kpi.ua/groups/?search=%D1%96%D0%BF-73', { json: true }, (err, res, body) => {
  if (err) { return console.log(err); }
  //console.log(body);
  data.id = body.results[0].id;
  console.log('$' + body.results[0].id);
  callback(null, data);
});

const fn2 = (data, callback) => {
  let url = 'https://api.rozklad.hub.kpi.ua/teachers/?search=' + encodeURI('Шемсединов');
  request(url, { json: true }, ( err, res, body) => {
    data.teacher_id_1 = body.results[0].id;
    //console.log(body);
    console.log('?'+body.results[0].id);
  });
  callback(null, data);
}

const fn3 = (data, callback) => {
  let url = 'https://api.rozklad.hub.kpi.ua/teachers/?search=' + encodeURI('Овчаренко');
  request(url, { json: true }, ( err, res, body) => {
    data.teacher_id_2 = body.results[0].id;
    console.log('!'+data.teacher_id_2);
  });
  //console.log(data);
  console.log(data.teacher_id_2);
  callback(null, data);
}

const func = (lecture_id, data) => {
  const url = 'https://api.rozklad.hub.kpi.ua/lessons/?groups=' + data.id + '&teachers=' + lecture_id;
  console.log(url);
  request(url, {json: true }, (err, res, body) => {
    let ans = body.results.length;
    console.log(body.results);
    console.log(lecture_id + ':' + ans);
  });
}

const fn4 = (data, callback) => {
  console.log(data);
  func(data.teacher_id_1, data);
  callback(null, data);
}

const fn5 = (data, callback) => {
  func(data.teacher_id_2, data);
  callback(null, data);
}

const x = (err, data) => {};
const w = metasync.parallel([fn2, fn3], obj, x);
const e = metasync.parallel([fn4, fn5], obj, x);

metasync.sequential([fn1, w, e], obj, x);
//metasync.flow([fn1, [[ [fn2, fn4], [fn3, fn5] ]] ])(obj, x);