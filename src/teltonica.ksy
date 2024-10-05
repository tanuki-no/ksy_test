meta:
  id:       teltonica_proto
  endian:   be
 
seq:
  - id:     preamble
    size:   4
    contents: [ 0x0, 0x0, 0x0, 0x0 ]
    doc:    Преамбула
  
  - id:     data_field_length
    type:   u4
    doc:    Размер данных начиная с поля Codec ID до поля Number of Data 2
  
  - id:     codec_id
    type:   u1
    enum:   codec_type
    doc:    Тип кодека
  
  - id:     number_of_data_1
    type:   u1
    doc:    Число записей в пакете
  
  - id:     avl_data
    type:   avl_data_type
    doc:    Содержимое пакета
 
  - id:     number_of_data_2
    type:   u1
    doc:    Число записей в пакете (соответствует значению Number of Data 1)
 
  - id:     crc16
    type:   u4
    doc:    Код CRC-16
 
types:
  avl_data_type:
    seq:
      - id:   timestamp
        type: u8
        doc:  Временная метка (64-бит)
 
      - id:   pri
        type: u1
        enum: priority_type
        doc:  Приоритет
 
      - id:   gps
        type: gps_data_type
        doc:  GPS Element
 
      - id:   id
        type: u1
        doc:  Event IO ID – if data is acquired on event – this field defines which IO property has changed and generated an event. If data cause is not event – the value is 0.
 
      - id:   n
        type: u1
        doc:  N = N1 + N2 + N3 + N4
 
      - id:   n1
        type: u1
        doc:  Number of properties, which length is 1 byte.
 
      - id:   n1_data
        type: n1_data_type
        doc:  One byte key-value pairs
        repeat: expr
        repeat-expr: n1
 
      - id:   n2
        type: u1
        doc:  Number of properties, which length is 2 byte.
 
      - id:   n2_data
        type: n2_data_type
        doc:  Two byte key-value pairs
        repeat: expr
        repeat-expr: n2
 
      - id:   n4
        type: u1
        doc:  Number of properties, which length is 4 byte.
 
      - id:   n4_data
        type: n4_data_type
        doc:  Four byte key-value pairs
        repeat: expr
        repeat-expr: n4
 
      - id:   n8
        type: u1
        doc:  Number of properties, which length is 8 byte.
 
      - id:   n8_data
        type: n8_data_type
        doc:  Four byte key-value pairs
        repeat: expr
        repeat-expr: n8
 
  gps_data_type:
    seq:
      - id: longitude
        type: s4
        doc: Долгота
 
      - id: latitude
        type: s4
        doc: Широта
 
      - id: altitude
        type: s2
        doc: Высота над уровнем моря
 
      - id: angle
        type: u2
        doc: Азимут в градусах по часовой стрелке
 
      - id:   satellites
        type: u1
        doc:  Количество видимых спутников
 
      - id:   speed
        type: u2
        doc:  Скорость в км/ч
 
  n1_data_type:
    seq:
      - id:   key
        type: u1
        doc:  Ключ
 
      - id:   value
        type: u1
        doc:  Значение
 
  n2_data_type:
    seq:
      - id:   key
        type: u1
        doc:  Ключ
 
      - id:   value
        type: u2
        doc:  Значение
 
  n4_data_type:
    seq:
      - id:   key
        type: u1
        doc:  Ключ
 
      - id:   value
        type: u4
        doc:  Значение
 
  n8_data_type:
    seq:
      - id:   key
        type: u1
        doc:  Ключ
 
      - id:   value
        type: u8
        doc:  Значение
 
enums:
  codec_type:
    0x08: codec8
    0x8E: codec8_extended
    0x10: codec16
    0x0C: codec12
    0x0D: codec13
    0x0E: codec14
 
  priority_type:
    0:  low
    1:  high
    2:  panic
